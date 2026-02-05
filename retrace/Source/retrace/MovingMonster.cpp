#include "MovingMonster.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "MyCharacter.h"
#include "SoundGameInstance.h"
#include "MovingMonsterAnimInstance.h"

// =====================
// Constructor
// =====================
AMovingMonster::AMovingMonster()
{
    PrimaryActorTick.bCanEverTick = true;

    GetCharacterMovement()->bOrientRotationToMovement = false;
    GetCharacterMovement()->bUseControllerDesiredRotation = false;
    GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;

    HitCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("HitCollision"));
    HitCollision->SetupAttachment(RootComponent);
    HitCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));


    GetCapsuleComponent()->SetNotifyRigidBodyCollision(true);
    GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

    MeshRoot = CreateDefaultSubobject<USceneComponent>(TEXT("MeshRoot"));
    MeshRoot->SetupAttachment(GetCapsuleComponent()); // Capsule を Root に
    GetMesh()->SetupAttachment(MeshRoot);

    // ゴール演出フラグ初期化
    bHasStartedRoar = false;
    bHasStartedTakeOff = false;

    // Mesh の初期回転を保存
    InitialMeshRotation = FRotator::ZeroRotator;
}

// =====================
// BeginPlay
// =====================
void AMovingMonster::BeginPlay()
{
    Super::BeginPlay();

    HitCollision->OnComponentBeginOverlap.AddDynamic(this, &AMovingMonster::OnOverlapBegin);
    GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AMovingMonster::OnMonsterHit);

    MonsterAnim = Cast<UMovingMonsterAnimInstance>(GetMesh()->GetAnimInstance());
    if (MonsterAnim)
    {
        MonsterAnim->OnMontageEnded.AddDynamic(this, &AMovingMonster::OnTakeOffMontageEnded);
    }

    // 初期 Forward 方向を保存（FlyForward 移動用）
    InitialForward = GetActorForwardVector();
    InitialMeshRotation = GetMesh()->GetRelativeRotation();
}
// =====================
// Tick
// =====================
void AMovingMonster::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if ((!bIsActive || bIsDead) && !bRotatingForTakeOff && !(MonsterAnim && MonsterAnim->bIsFlying))
        return;

    // 通常移動（Ground）
    if (bIsActive && !bIsDead && !(MonsterAnim && MonsterAnim->bIsFlying))
    {
        FVector NewLocation = GetActorLocation() + GetActorForwardVector() * MoveSpeed * DeltaTime;
        SetActorLocation(NewLocation, false);
    }

    // FlyForward 移動（Capsule は動かさず、Mesh の見た目だけ回転）
    if (MonsterAnim && MonsterAnim->bIsFlying)
    {
        // Actor の前方向の逆向きで移動（反対方向に飛ぶ）
        FVector FlyDir = -GetActorForwardVector();

        SetActorLocation(GetActorLocation() + FlyDir * FlySpeed * DeltaTime, false);

        // Mesh はTakeOffの回転のまま維持（見た目だけ）
       
    }








    // TakeOff 回転処理（見た目だけ）
    if (bRotatingForTakeOff)
    {
        TakeOffRotateElapsed += DeltaTime;
        float Alpha = FMath::Clamp(TakeOffRotateElapsed / TakeOffRotateDuration, 0.f, 1.f);

        FRotator NewRot = FMath::Lerp(TakeOffStartMeshRotation, TakeOffTargetMeshRotation, Alpha);
        GetMesh()->SetRelativeRotation(NewRot);

        if (Alpha >= 1.f)
        {
            bRotatingForTakeOff = false;
            GetMesh()->SetRelativeRotation(TakeOffTargetMeshRotation);
        }
    }
}


// =====================
// 通常挙動
// =====================
void AMovingMonster::ActivateMonster()
{
    bIsActive = true;
}

void AMovingMonster::OnOverlapBegin(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    AMyCharacter* Player = Cast<AMyCharacter>(OtherActor);
    if (!Player) return;

    Player->PlayKnockDown();
}

// =====================
// ゴール演出開始
// =====================
void AMovingMonster::OnGoalReached()
{
    if (bIsDead) return;

    bIsDead = true;
    bIsActive = false;
    USoundGameInstance* GI =
        Cast<USoundGameInstance>(UGameplayStatics::GetGameInstance(this));
    if (!GI)return;
    GI->bShouldPlayBGM = false;

    // ❌ DisableMovement は使わない
    GetCharacterMovement()->StopMovementImmediately();
    GetCharacterMovement()->SetMovementMode(MOVE_None);

    if (MonsterAnim && MonsterAnim->RoarMontage)
    {
        FOnMontageEnded EndDelegate;
        EndDelegate.BindUObject(this, &AMovingMonster::OnRoarMontageEnded);

        MonsterAnim->Montage_Play(MonsterAnim->RoarMontage);
        MonsterAnim->Montage_SetEndDelegate(
            EndDelegate,
            MonsterAnim->RoarMontage
        );
    }
}


void AMovingMonster::OnRoarMontageEnded(
    UAnimMontage* Montage,
    bool bInterrupted)
{
    if (bInterrupted) return;

    if (MonsterAnim && MonsterAnim->TakeOffMontage)
    {
        MonsterAnim->Montage_Play(MonsterAnim->TakeOffMontage);

        // ★ メッシュだけ回す
        bRotatingForTakeOff = true;
        TakeOffRotateElapsed = 0.f;

        TakeOffStartMeshRotation = GetMesh()->GetRelativeRotation();
        TakeOffTargetMeshRotation =
            TakeOffStartMeshRotation + FRotator(0.f, 180.f, 0.f);
    }
}

void AMovingMonster::OnTakeOffMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
    if (bInterrupted || !MonsterAnim || Montage != MonsterAnim->TakeOffMontage)
        return;

    MonsterAnim->bIsFlying = true;

    // 少し浮かせる
    FVector Loc = GetActorLocation();
    Loc.Z += 10.f;
    SetActorLocation(Loc, false);

    // Mesh の回転を正しく設定
    FRotator MeshRot = InitialMeshRotation; // BPで設定した回転を基準に
    MeshRot.Yaw += 180.f;                   // 奥に進むように反転
    GetMesh()->SetRelativeRotation(MeshRot);

    // TickでMeshを回転させない
    bRotatingForTakeOff = false;

    \

    // 移動モード
    UCharacterMovementComponent* MoveComp = GetCharacterMovement();
    MoveComp->SetMovementMode(MOVE_Flying);
    MoveComp->GravityScale = 0.f;
    MoveComp->MaxFlySpeed = FlySpeed;


    //クリアwidget表示
    if (AMyCharacter* Player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerPawn(this, 0)))
    {
        GetWorldTimerManager().SetTimer(
            ClearWidgetTimerHandle, // FTimerHandle メンバ変数
            [Player]() { Player->PlayClearWhidget(); },
            1.0f, // 秒数
            false
        );
    }

}


void AMovingMonster::StartFlyForward()
{
    MonsterAnim->bIsFlying = true;

    // FlyForwardが始まったタイミングでタイマーセット
    float Delay = 0.5f; // 秒数、再生開始からの時間
}



// =====================
// ヒットSE
// =====================
void AMovingMonster::OnMonsterHit(
    UPrimitiveComponent* HitComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    FVector NormalImpulse,
    const FHitResult& Hit)
{
    if (!bCanPlayHitSound || !HitSound) return;
    USoundGameInstance* GI =
        Cast<USoundGameInstance>(UGameplayStatics::GetGameInstance(this));
    if (!GI)return;
    if (!wallbreak)
    {
        if (OtherComp && OtherComp->IsA<UGeometryCollectionComponent>())
        {

            UGameplayStatics::PlaySoundAtLocation(this, HitSound, Hit.ImpactPoint);
            bCanPlayHitSound = false;
            wallbreak = true;
            GI->bShouldPlayBGM = true;
            GetWorldTimerManager().SetTimer(HitSoundTimer, [this]()
                {
                    bCanPlayHitSound = true;
                }, HitSoundCooldown, false);
        }
    }
    
}
