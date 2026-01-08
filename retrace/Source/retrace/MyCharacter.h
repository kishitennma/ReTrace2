#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Animation/AnimMontage.h"
#include "MyCharacter.generated.h"



class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class USoundBase;
struct FInputActionValue;

UCLASS()
class RETRACE_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMyCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void NotifyControllerChanged() override;

	// 移動アクション
	void Move(const FInputActionValue& Value);

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveAction;

	

	UFUNCTION()
	void PlayKnockDown();


	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* KnockDownMontage;

	bool bIsKnockedDown = false;

	// ★ 足音
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* FootstepSound;

	bool bIsMoving = false;
	float FootstepTimer = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Sound")
	float FootstepInterval = 0.4f;  // 足音の間隔

	// ★ カメラ揺れ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Shake")
	float ShakeIntensity = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Shake")
	float ShakeDuration = 1.0f;

	bool bIsShaking = false;
	float ShakeTimer = 0.0f;
	FVector OriginalCameraOffset;

	UFUNCTION()
	void StartCameraShake(float Intensity, float Duration);

private:
	float DefaultDistance;
	FRotator DefaultAngle;
	FVector DefaultOffset;
};
