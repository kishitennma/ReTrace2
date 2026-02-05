// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterWingNotify.h"
#include "retrace/MovingMonster.h"
#include "Kismet/GameplayStatics.h"

void UMonsterWingNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (AMovingMonster* Monster = Cast<AMovingMonster>(MeshComp->GetOwner()))
    {
        if (Monster->MonsterWing)
        {
            UGameplayStatics::PlaySoundAtLocation(Monster, Monster->MonsterWing, Monster->GetActorLocation());

        }
    }
}