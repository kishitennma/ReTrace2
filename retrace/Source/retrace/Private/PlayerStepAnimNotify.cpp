// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStepAnimNotify.h"
#include "retrace/MyCharacter.h"
#include "Kismet/GameplayStatics.h"

void UPlayerStepAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (AMyCharacter* character = Cast<AMyCharacter>(MeshComp->GetOwner()))
    {
        if (character->FootstepSound )
        {
            UGameplayStatics::PlaySoundAtLocation(character, character->FootstepSound, character->GetActorLocation());
          
        }
    }
}