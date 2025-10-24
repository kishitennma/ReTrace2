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

    // �����̈ʒu�E��]�� Spawn�I
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
