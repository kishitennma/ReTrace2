// MovingMonsterAnimInstance.h
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MovingMonsterAnimInstance.generated.h"

UCLASS()
class RETRACE_API UMovingMonsterAnimInstance : public UAnimInstance
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    UAnimMontage* RoarMontage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    UAnimMontage* TakeOffMontage;

    // FlyForward ÇÕ StateMachine ÇÃ bool Ç≈êßå‰
    UPROPERTY(BlueprintReadWrite, Category = "Animation")
    bool bIsFlying = false;

    // --------------------
    // C++Ç©ÇÁåƒÇ‘ä÷êî
    // --------------------
    UFUNCTION(BlueprintCallable)
    void PlayRoar();

    UFUNCTION(BlueprintCallable)
    void PlayTakeOff();
};
