#include "MovingMonsterAnimInstance.h"
#include "retrace/MovingMonster.h"

void UMovingMonsterAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    Monster = Cast<AMovingMonster>(TryGetPawnOwner());

    MontageEndDelegate.BindUObject(
        this,
        &UMovingMonsterAnimInstance::HandleMontageEnded
    );

    if (Monster)
    {
        bIsDead = Monster->bIsDead; // Monsterのフラグをコピー
    }

    Montage_SetEndDelegate(MontageEndDelegate);
}


void UMovingMonsterAnimInstance::HandleMontageEnded(
    UAnimMontage* Montage,
    bool bInterrupted
)
{
    if (!Monster || bInterrupted) return;

    Monster->OnDeathAnimationFinished();
}
