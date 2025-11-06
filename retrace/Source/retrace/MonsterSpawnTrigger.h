#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingMonster.h" 
#include "MonsterSpawnTrigger.generated.h"

UCLASS()
class RETRACE_API AMonsterSpawnTrigger : public AActor
{
    GENERATED_BODY()

public:
    AMonsterSpawnTrigger();

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnOverlapBegin(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );

    

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn") 
        TSubclassOf<AMovingMonster> MonsterClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
    AActor* SpawnPoint; // 置いたアクタの Transform を使える

    // ---- カメラ変更設定 ----
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
    FVector NewCameraOffset ;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
    FRotator NewCameraRotation ;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Change")
    float NewCameraDistance ;

private:
    UPROPERTY(VisibleAnywhere)
    class UBoxComponent* TriggerBox;

    

  

    bool bHasSpawned = false;
};
