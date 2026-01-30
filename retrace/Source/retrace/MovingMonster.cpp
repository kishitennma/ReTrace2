#include "MovingMonster.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "MyCharacter.h"
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

    // ゴール演出フラグ初期化
    bHasStartedRoar = false;
    bHasStartedTakeOff = false;
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
    if (!MonsterAnim)
    {
        UE_LOG(LogTemp, Error, TEXT("MonsterAnim is NULL"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("MonsterAnim OK"));
    }
}

// =====================
// Tick
// =====================
void AMovingMonster::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!bIsActive || bIsDead) return;

    FVector NewLocation = GetActorLocation() + GetActorForwardVector() * MoveSpeed * DeltaTime;
    SetActorLocation(NewLocation, false);
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

    GetCharacterMovement()->StopMovementImmediately();
    GetCharacterMovement()->DisableMovement();
    GetCharacterMovement()->Velocity = FVector::ZeroVector;

    // --------------------
    // 咆哮開始（Montage再生）
    // --------------------
    if (MonsterAnim && !bHasStartedRoar)
    {
        if (MonsterAnim->RoarMontage)
        {
            bHasStartedRoar = true;
            MonsterAnim->Montage_Play(MonsterAnim->RoarMontage);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("RoarMontage is NULL! Check AnimBP"));
        }
    }
}

// =====================
// AnimNotify から呼ばれる
// =====================
void AMovingMonster::OnRoarFinished()
{
    if (MonsterAnim && !bHasStartedTakeOff)
    {
        if (MonsterAnim->TakeOffMontage)
        {
            bHasStartedTakeOff = true;
            MonsterAnim->Montage_Play(MonsterAnim->TakeOffMontage);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("TakeOffMontage is NULL! Check AnimBP"));
        }
    }
}

void AMovingMonster::OnTakeOffFinished()
{
    bIsFlying = true;

    // ここが「逃げ切った」タイミング
    AMyCharacter* Player = Cast<AMyCharacter>(
        UGameplayStatics::GetActorOfClass(GetWorld(), AMyCharacter::StaticClass()));

    if (Player)
    {
        Player->PlayClearWhidget();
    }
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

    if (OtherComp && OtherComp->IsA<UGeometryCollectionComponent>())
    {
        UGameplayStatics::PlaySoundAtLocation(this, HitSound, Hit.ImpactPoint);
        bCanPlayHitSound = false;

        GetWorldTimerManager().SetTimer(HitSoundTimer, [this]()
            {
                bCanPlayHitSound = true;
            }, HitSoundCooldown, false);
    }
}
