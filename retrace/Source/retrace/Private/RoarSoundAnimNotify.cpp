// RoarSoundNotify.cpp
#include "retrace/public/RoarSoundAnimNotify.h"
#include "retrace/MovingMonster.h"
#include "Kismet/GameplayStatics.h"

void URoarSoundAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
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
