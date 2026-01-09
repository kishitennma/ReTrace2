// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyCharacter.h"

void UMyAnimInstance::NativeInitializeAnimation()
{
	if (MyChar == nullptr)
	{
		MyChar = Cast<AMyCharacter>(TryGetPawnOwner());
	}
}

void UMyAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (MyChar == nullptr)
	{
		MyChar = Cast<AMyCharacter>(TryGetPawnOwner());
	}
	if (MyChar)
	{
		FVector Velocity = MyChar->GetVelocity();
		Velocity.Z = 0;
		Speed = Velocity.Size();
		bIsInAir = MyChar->GetMovementComponent()->IsFalling();
		if (MyChar->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f)
		{
			bIsAccelerating = true;
		}
		else
		{
			bIsAccelerating = false;
		}
	}
}




