#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "MonsterEffectManager.generated.h"

class APostProcessVolume;
class AMovingMonster;

class ACharacter;

UCLASS()
class RETRACE_API AMonsterEffectManager : public AActor
{
    GENERATED_BODY()

public:
    AMonsterEffectManager();
    virtual void Tick(float DeltaTime) override;
    // 呼ばれたときにエフェクトを更新
    void UpdateEffect(ACharacter* Player, AActor* Monster);

    UPROPERTY()
    ACharacter* PlayerRef;

    UPROPERTY()
    AActor* MonsterRef;

    UFUNCTION(BlueprintCallable)
    void SetTargets(ACharacter* Player, AActor* Monster);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
    TSubclassOf<AMovingMonster> MonsterClass;

   

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
    AActor* SpawnPoint;

    

protected:
    virtual void BeginPlay() override;

private:
    // ポストプロセスボリューム
    APostProcessVolume* PostProcessVolume;
   
    // 赤み・Vignette・揺れ強度
    float CurrentIntensity;

    // カメラ揺れの最大幅
    float ShakeAmount;
};
