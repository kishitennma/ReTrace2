#include "MovingMonsterAnimInstance.h"
#include "retrace/MovingMonster.h"

void UMovingMonsterAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    OwnerMonster = Cast<AMovingMonster>(TryGetPawnOwner());
}

void UMovingMonsterAnimInstance::PlayRoar()
{
    if (RoarMontage)
    {
        Montage_Play(RoarMontage);
    }
}

void UMovingMonsterAnimInstance::PlayTakeOff()
{
    if (TakeOffMontage)
    {
        Montage_Play(TakeOffMontage);
    }
}
