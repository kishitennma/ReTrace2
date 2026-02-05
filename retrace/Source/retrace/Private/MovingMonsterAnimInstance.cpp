// MovingMonsterAnimInstance.cpp
#include "MovingMonsterAnimInstance.h"
#include "retrace/MovingMonster.h"    
#include "Animation/AnimInstance.h"
#include "Kismet/GameplayStatics.h"
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

void UMovingMonsterAnimInstance::Notify_RoarSound(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (AMovingMonster* Monster = Cast<AMovingMonster>(MeshComp->GetOwner()))
    {
        if (Monster->RoarSound && Monster->bCanPlayRoarSound)
        {
            UGameplayStatics::PlaySoundAtLocation(Monster, Monster->RoarSound, Monster->GetActorLocation());
            Monster->bCanPlayRoarSound = false;
        }
    }
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
