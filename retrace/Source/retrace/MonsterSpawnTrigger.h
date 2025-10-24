#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MonsterSpawnTrigger.generated.h"

class UBoxComponent;
class AMovingMonster;
class ASpawnPointActor;

UCLASS()
class RETRACE_API AMonsterSpawnTrigger : public AActor
{
    GENERATED_BODY()

public:
    AMonsterSpawnTrigger();

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(VisibleAnywhere)
    UBoxComponent* TriggerBox;

    // Monster BP
    UPROPERTY(EditAnywhere, Category = "Spawn")
    TSubclassOf<AMovingMonster> MonsterClass;

    // Åö ÉåÉxÉãÇ…íuÇ¢ÇΩ SpawnPoint ÇÃéQè∆
    UPROPERTY(EditAnywhere, Category = "Spawn")
    ASpawnPointActor* SpawnPoint;

    UFUNCTION()
    void OnOverlapBegin(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );
};
