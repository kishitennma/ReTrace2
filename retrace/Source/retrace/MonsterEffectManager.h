#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MonsterEffectManager.generated.h"

UCLASS(Blueprintable)
class RETRACE_API AMonsterEffectManager : public AActor
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
    class APostProcessVolume* TargetPostProcess;

    UFUNCTION(BlueprintCallable, Category = "Effect")
    void ApplyEffect(float Intensity);

    UFUNCTION(BlueprintCallable, Category = "Effect")
    void ClearEffect();
};
