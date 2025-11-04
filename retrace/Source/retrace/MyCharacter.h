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

	/** カスタムカメラ設定（BPから変更可能） */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Custom")
	float CameraDistance = 400.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Custom")
	FRotator CameraAngle = FRotator(-10.f, 0.f, 0.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Custom")
	FVector CameraOffset = FVector(0.f, 0.f, 100.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Custom")
	bool bUseCustomCamera = false;

private:
	float DefaultDistance;
	FRotator DefaultAngle;
	FVector DefaultOffset;
};
