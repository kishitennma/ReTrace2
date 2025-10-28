#include "MovingMonster.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

AMovingMonster::AMovingMonster()
{
    PrimaryActorTick.bCanEverTick = true;

    // �L�����ړ��R���|�[�l���g�̐ݒ��i�����j
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

    if (bIsActive)
    {
        FVector NewLocation = GetActorLocation() + GetActorForwardVector() * MoveSpeed * DeltaTime;
        SetActorLocation(NewLocation, false); 
    }

    
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
    if (OtherActor && OtherActor != this)
    {
        if (OtherActor->IsA(ACharacter::StaticClass()))
        {
            UGameplayStatics::OpenLevel(
                this,
                FName(*GetWorld()->GetName())
            );
        }
    }
}



