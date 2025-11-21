// MyCharacter.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
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
	/** カメラ用スプリングアーム（追従） */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	USpringArmComponent* CameraBoom;

	/** フォローカメラ */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* FollowCamera;

	/** 入力マッピング */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* DefaultMappingContext;

	/** 移動アクション */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveAction;

	
	//カメラの揺れ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Custom")
	bool bUseCustomCamera = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Shake")
	float ShakeIntensity = 20.0f;   // 揺れの強さ（位置揺れ）

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Shake")
	float ShakeDuration = 1.0f;     // 継続時間

	float ShakeTimer = 0.0f;
	bool bIsShaking = false;

	UFUNCTION()
	void StartCameraShake(float Intensity, float Duration);


private:
	float DefaultDistance;
	FRotator DefaultAngle;
	FVector DefaultOffset;




	
	
	FVector OriginalCameraOffset;
};
