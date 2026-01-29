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

    // Monster èÛë‘
    UPROPERTY(BlueprintReadOnly)
    bool bIsFlying = false;

    // Montages
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim")
    UAnimMontage* RoarMontage;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim")
    UAnimMontage* TakeOffMontage;

    /** åƒÇ—èoÇµóp */
    void PlayRoar();
    void PlayTakeOff();

private:
    UPROPERTY()
    AMovingMonster* OwnerMonster;
};
