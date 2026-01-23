#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MovingMonsterAnimInstance.generated.h"

class AMovingMonster;

UCLASS()
class RETRACE_API UMovingMonsterAnimInstance : public UAnimInstance
{
    GENERATED_BODY()

public:
    virtual void NativeInitializeAnimation() override;

    UFUNCTION()
    void HandleMontageEnded(UAnimMontage* Montage, bool bInterrupted);

    UPROPERTY(BlueprintReadWrite, Category = "Animation")
    bool bIsDead;

private:
    AMovingMonster* Monster = nullptr;

    FOnMontageEnded MontageEndDelegate;
};
