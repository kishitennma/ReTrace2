#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Animation/AnimMontage.h"
#include "MonsterEffectManager.h"
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
	UFUNCTION()
	void PlayerGoal();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void NotifyControllerChanged() override;

	UFUNCTION()
	void OnDeathFadeFinished();
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

	UFUNCTION(BlueprintCallable)
	void ApplyClearCamera(
		FRotator CameraRotation,
		float CameraDistance,
		FVector CameraOffset
	);

	UFUNCTION(BlueprintCallable)
	void ApplyDeathCamera(
		FRotator CameraRotation,
		float CameraDistance,
		FVector CameraOffset
	);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> DeathWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> ClearWidgetClass;

	// ▼ 実際に生成されるウィジットのインスタンス
	UPROPERTY()
	UUserWidget* DeathWidget;
	UPROPERTY()
	UUserWidget* ClearWidget;


	UFUNCTION()
	void Retry();

	UFUNCTION()
	void PlayKnockDown();

	UFUNCTION()
	void PlayClearWhidget();


	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* KnockDownMontage;

	bool bIsKnockedDown = false;

	// ★ 足音
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* FootstepSound;
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* gogogosound;
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* Knock;
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* clear;

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

	UPROPERTY()
	AMonsterEffectManager* MonsterEffectManager;

private:
	float DefaultDistance;
	FRotator DefaultAngle;
	FVector DefaultOffset;
};
