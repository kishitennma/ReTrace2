// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class RETRACE_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;

	UFUNCTION(BlueprintCallable, Category = Animation)
	void UpdateAnimationProperties(float DeltaTime);

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = Movement)
	float Speed;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = Movement)
	bool bIsAccelerating;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = Movement)
	bool bIsInAir;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = Movement)
	class AMyCharacter* MyChar;
	
};
