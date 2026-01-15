#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "Delegates/DelegateCombinations.h"
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

    void OnDeathFadeFinished();

public:
    void StartDeathFade();
    void UpdateDeathFade(float DeltaTime);

    UPROPERTY()
    ACharacter* PlayerRef;

    UPROPERTY()
    AActor* MonsterRef;

    UFUNCTION(BlueprintCallable)
    void SetTargets(ACharacter* Player, AActor* Monster);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
    TSubclassOf<AMovingMonster> MonsterClass;

    UPROPERTY(EditAnywhere, Category = "Death Fade")
    float DeathFadeSpeed = 0.5f; // 小さいほどゆっくり

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
    AActor* SpawnPoint;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathFadeFinished);

    UPROPERTY(BlueprintAssignable)
    FOnDeathFadeFinished OnDeathFadeFinishedEvent;

    // フェード完了までの時間（秒）
    UPROPERTY(EditAnywhere, Category = "Death")
    float DeathFadeDuration = 1.3f;

protected:
    virtual void BeginPlay() override;

private:
    // ポストプロセスボリューム
    APostProcessVolume* PostProcessVolume;
   
    // 赤み・Vignette・揺れ強度
    float CurrentIntensity;

    // カメラ揺れの最大幅
    float ShakeAmount;

    // フェード用
    bool bIsDying = false;

    float DeathFadeAlpha = 0.0f;

    

};
