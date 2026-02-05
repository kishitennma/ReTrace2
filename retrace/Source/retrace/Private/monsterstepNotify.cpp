// Fill out your copyright notice in the Description page of Project Settings.


#include "monsterstepNotify.h"
#include "retrace/MovingMonster.h"
#include "Kismet/GameplayStatics.h"

void UmonsterstepNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (AMovingMonster* Monster = Cast<AMovingMonster>(MeshComp->GetOwner()))
    {
        if (Monster->MonsterStep &&Monster->wallbreak)
        {
            UGameplayStatics::PlaySoundAtLocation(Monster, Monster->MonsterStep, Monster->GetActorLocation());
            
        }
    }
}