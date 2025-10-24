#include "SpawnPointActor.h"
#include "MovingMonster.h"
#include "Kismet/GameplayStatics.h"

ASpawnPointActor::ASpawnPointActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ASpawnPointActor::SpawnMonster()
{
    if (!MonsterClass) return;

    FActorSpawnParameters Params;

    // Ž©•ª‚ÌˆÊ’uE‰ñ“]‚Å SpawnI
    FTransform SpawnTransform = GetActorTransform();

    AMovingMonster* Monster = GetWorld()->SpawnActor<AMovingMonster>(
        MonsterClass,
        SpawnTransform,
        Params
    );

    if (Monster)
    {
        Monster->ActivateMonster();
    }
}
