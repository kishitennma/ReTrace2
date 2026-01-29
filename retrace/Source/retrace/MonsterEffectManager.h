#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MonsterEffectManager.generated.h"

class APostProcessVolume;
class ACharacter;
class USoundBase;

UCLASS()
class RETRACE_API AMonsterEffectManager : public AActor
{
    GENERATED_BODY()

public:
    AMonsterEffectManager();
    virtual void Tick(float DeltaTime) override;

    // 対象セット
    UFUNCTION(BlueprintCallable)
    void SetTargets(ACharacter* Player, AActor* Monster);

    // ===== 死亡フェード =====
    void StartDeathFade();
    void ResetDeathState();

    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathFadeFinished);

    UPROPERTY(BlueprintAssignable)
    FOnDeathFadeFinished OnDeathFadeFinishedEvent;

protected:
    virtual void BeginPlay() override;

private:
    // ===== 内部処理 =====
    void UpdateEffect(float DeltaTime);
    void UpdateDeathFade(float DeltaTime);
    void HandleProximitySE(float Distance);
    void HandlePostProcess(float Distance);

    void OnDeathFadeFinished();

private:
    // ===== 参照 =====
    UPROPERTY()
    ACharacter* PlayerRef = nullptr;

    UPROPERTY()
    AActor* MonsterRef = nullptr;

    APostProcessVolume* PostProcessVolume = nullptr;

    // ===== 距離演出 =====
    UPROPERTY(EditAnywhere, Category = "Proximity")
    float EffectStartDistance = 1000.f;   // フェード開始距離

    UPROPERTY(EditAnywhere, Category = "Proximity")
    float ProximitySEDistance = 500.f;    // SEが鳴る距離

    UPROPERTY(EditAnywhere, Category = "Proximity")
    USoundBase* ProximitySE = nullptr;

    bool bIsPlayerInsideSEArea = false;

    // ===== 死亡フェード =====
    UPROPERTY(EditAnywhere, Category = "Death")
    float DeathFadeDuration = 1.3f;

    bool bIsDying = false;
    float DeathFadeAlpha = 0.f;
};
