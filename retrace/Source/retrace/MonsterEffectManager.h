#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraShakeBase.h"
#include "Engine/PostProcessVolume.h"
#include "MonsterEffectManager.generated.h"


class AMovingMonster;
UCLASS()
class RETRACE_API AMonsterEffectManager : public AActor
{
    GENERATED_BODY()

public:
    AMonsterEffectManager();

    //virtual void Tick(float DeltaTime);
    virtual void BeginPlay() override;

    // MonsterEffectManager.h
    UPROPERTY()
    AMovingMonster* Monster;

    UPROPERTY()
    ACharacter* Player;


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PostProcess")
    APostProcessVolume* PostProcessVolume;

    // “G‚ª‹ß‚Ã‚¢‚½‚Æ‚«‚ÉŒÄ‚Ô
    UFUNCTION(BlueprintCallable)
    void ApplyEffect(float Intensity);

    UFUNCTION(BlueprintCallable)
    void ClearEffect();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shake")
    TSubclassOf<UCameraShakeBase> CameraShakeClass;

private:
    float CurrentIntensity = 0.0f;
};
