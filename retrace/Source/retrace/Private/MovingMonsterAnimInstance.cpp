// MovingMonsterAnimInstance.cpp
#include "MovingMonsterAnimInstance.h"
#include "Kismet/KismetSystemLibrary.h"

void UMovingMonsterAnimInstance::PlayRoar()
{
    if (!RoarMontage)
    {
        UE_LOG(LogTemp, Error, TEXT("RoarMontage is NULL! Check AnimBP"));
        return;
    }

    // すでに再生中ならスキップ
    if (Montage_IsPlaying(RoarMontage))
    {
        UE_LOG(LogTemp, Warning, TEXT("RoarMontage is already playing"));
        return;
    }

    Montage_Play(RoarMontage);
}

void UMovingMonsterAnimInstance::PlayTakeOff()
{
    if (!TakeOffMontage)
    {
        UE_LOG(LogTemp, Error, TEXT("TakeOffMontage is NULL! Check AnimBP"));
        return;
    }

    // すでに再生中ならスキップ
    if (Montage_IsPlaying(TakeOffMontage))
    {
        UE_LOG(LogTemp, Warning, TEXT("TakeOffMontage is already playing"));
        return;
    }

    Montage_Play(TakeOffMontage);
}
