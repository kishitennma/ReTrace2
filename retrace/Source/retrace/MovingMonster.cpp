#include "MovingMonster.h"



AMovingMonster::AMovingMonster()
{
    PrimaryActorTick.bCanEverTick = true;
  
}

void AMovingMonster::BeginPlay()
{
    Super::BeginPlay();
}

void AMovingMonster::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bIsActive)
    {
        // Forward�����ֈړ���������
        FVector NewLocation = GetActorLocation() + GetActorForwardVector() * MoveSpeed * DeltaTime;
        SetActorLocation(NewLocation);
    }
}

void AMovingMonster::ActivateMonster()
{
    bIsActive = true;
}
