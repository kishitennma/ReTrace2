#include "MovingMonster.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "MyCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

AMovingMonster::AMovingMonster()
{
    PrimaryActorTick.bCanEverTick = true;

    // キャラ移動コンポーネントの設定例（調整可）
    GetCharacterMovement()->bOrientRotationToMovement = false;
    GetCharacterMovement()->bUseControllerDesiredRotation = false;
    GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;

    HitCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("HitCollision"));
    HitCollision->SetupAttachment(RootComponent);
    HitCollision->SetCollisionProfileName("OverlapAllDynamic");
}

void AMovingMonster::BeginPlay()
{
    Super::BeginPlay();

    HitCollision->OnComponentBeginOverlap.AddDynamic(this, &AMovingMonster::OnOverlapBegin);
}

void AMovingMonster::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!bIsActive || bIsDead) return;

    FVector NewLocation =
        GetActorLocation() + GetActorForwardVector() * MoveSpeed * DeltaTime;
    SetActorLocation(NewLocation, false);
}


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
    const FHitResult& SweepResult
)
{


    AMyCharacter* Player = Cast<AMyCharacter>(OtherActor);
    if (Player)
    {
        Player->PlayKnockDown();
    }
   
}

void AMovingMonster::OnGoalReached()
{

    PlayDeath();
}


void AMovingMonster::PlayDeath()
{
    if (bIsDead) return;
    bIsDead = true;
    bIsActive = false;

    // 移動完全停止
    GetCharacterMovement()->StopMovementImmediately();
    GetCharacterMovement()->DisableMovement();

    // AnimBP が参照している値をゼロにする
    GetCharacterMovement()->Velocity = FVector::ZeroVector;

    if (UAnimInstance* Anim = GetMesh()->GetAnimInstance())
    {
        Anim->Montage_Play(DeathMontage);
    }

    AMyCharacter* Player = Cast<AMyCharacter>(
        UGameplayStatics::GetActorOfClass(
            GetWorld(),
            AMyCharacter::StaticClass()
        )
    );
    if (!Player) return;
    if(Player)
    Player->PlayClearWhidget();
}



//void AMovingMonster::OnDeathAnimationFinished()
//{
//    UE_LOG(LogTemp, Warning, TEXT("Monster Death Animation Finished"));
//
//    if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
//    {
//        AnimInstance->Montage_Play(DeathLooptMontage);
//    }
//}

