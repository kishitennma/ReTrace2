#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnPointActor.generated.h"

UCLASS()
class RETRACE_API ASpawnPointActor : public AActor
{
    GENERATED_BODY()

public:
    ASpawnPointActor();

    // モンスターをここにスポーンさせたい場合に使用
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
    TSubclassOf<class AMovingMonster> MonsterClass;

    UFUNCTION(BlueprintCallable)
    void SpawnMonster();
};
