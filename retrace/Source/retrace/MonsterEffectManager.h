#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MonsterEffectManager.generated.h"

class AMovingMonster;
class AMyCharacter;
class APostProcessVolume;

UCLASS()
class RETRACE_API AMonsterEffectManager : public AActor
{
    GENERATED_BODY()

public:
    AMonsterEffectManager();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    void ApplyEffect(float Intensity);
    void ClearEffect();

private:
    UPROPERTY()
    APostProcessVolume* PostProcessVolume;

    UPROPERTY()
    AMovingMonster* Monster;

    UPROPERTY()
    AMyCharacter* Player;

    float CurrentIntensity = 0.f;
    float MaxDistance = 2000.f; // エフェクトが最大になる距離

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraShake")
    TSubclassOf<class UCameraShakeBase> CameraShakeClass;
};
