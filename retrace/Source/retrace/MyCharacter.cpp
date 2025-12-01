// MyCharacter.cpp

#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"

AMyCharacter::AMyCharacter()
{
	// 衝突カプセル設定
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// キャラクターの回転設定
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 500, 0);

	// ★ SpringArm設定
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	// 親（キャラクター）の回転を一切継承しない
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritYaw = false;
	CameraBoom->bInheritRoll = false;

	// 角度を絶対指定（＝ステージ奥方向固定）
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->SetWorldRotation(FRotator(-10.f, 0.f, 0.f)); // ←ここを基準方向に調整

	// 位置（高さ）をキャラから固定オフセット
	CameraBoom->SetRelativeLocation(FVector(0.f, 0.f, 80.f));
	CameraBoom->TargetArmLength = 400.f;
	CameraBoom->bDoCollisionTest = false;

	

	// ★ カメラ設定
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->bUsePawnControlRotation = false;
}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// デフォルト値保存
	DefaultDistance = CameraBoom->TargetArmLength;
	DefaultAngle = CameraBoom->GetRelativeRotation();
	DefaultOffset = CameraBoom->SocketOffset;
}

void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsShaking && CameraBoom)
	{
		ShakeTimer += DeltaTime;
		float Alpha = ShakeTimer / ShakeDuration;

		// 時間経過で揺れが減衰
		float CurrentIntensity = ShakeIntensity * (1.0f - Alpha);

		if (CurrentIntensity <= 0.0f)
		{
			bIsShaking = false;
			// 元のオフセットに戻す
		//	CameraBoom->SetRelativeLocation(OriginalCameraOffset);
			return;
		}

		// ランダム揺れ
		float OffsetX = FMath::FRandRange(-1.f, 1.f) * CurrentIntensity;
		float OffsetY = FMath::FRandRange(-1.f, 1.f) * CurrentIntensity;
		float OffsetZ = FMath::FRandRange(-1.f, 1.f) * CurrentIntensity * 0.5f;

		CameraBoom->SetRelativeLocation(OriginalCameraOffset + FVector(OffsetX, OffsetY, OffsetZ));
	}
}

void AMyCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	if (APlayerController* PC = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);
	}
}

void AMyCharacter::Move(const FInputActionValue& Value)
{
	FVector2D InputVector = Value.Get<FVector2D>();
	if (Controller == nullptr) return;

	const FRotator ControlRot = Controller->GetControlRotation();
	const FRotator YawRot(0, ControlRot.Yaw, 0);

	const FVector Forward = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
	const FVector Right = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);

	AddMovementInput(Forward, InputVector.Y);
	AddMovementInput(Right, InputVector.X);
}

void AMyCharacter::StartCameraShake(float Intensity, float Duration)
{
	if (!CameraBoom) return;

	OriginalCameraOffset = CameraBoom->GetRelativeLocation();
	ShakeIntensity = Intensity;
	ShakeDuration = Duration;
	ShakeTimer = 0.f;
	bIsShaking = true;
}

