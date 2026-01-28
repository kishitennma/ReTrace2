#include "MovingMonsterAnimInstance.h"
#include "retrace/MovingMonster.h"

void UMovingMonsterAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    Monster = Cast<AMovingMonster>(TryGetPawnOwner());

    

    if (Monster)
    {
        bIsDead = Monster->bIsDead; // Monsterのフラグをコピー
    }

    Montage_SetEndDelegate(MontageEndDelegate);
}


