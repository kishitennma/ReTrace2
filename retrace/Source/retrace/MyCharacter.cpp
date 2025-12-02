// MyCharacter.cpp

#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AMyCharacter::AMyCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 500, 0);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritYaw = false;
	CameraBoom->bInheritRoll = false;

	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->SetWorldRotation(FRotator(-10.f, 0.f, 0.f));

	CameraBoom->SetRelativeLocation(FVector(0.f, 0.f, 80.f));
	CameraBoom->TargetArmLength = 400.f;
	CameraBoom->bDoCollisionTest = false;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->bUsePawnControlRotation = false;
}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	DefaultDistance = CameraBoom->TargetArmLength;
	DefaultAngle = CameraBoom->GetRelativeRotation();
	DefaultOffset = CameraBoom->SocketOffset;
}

void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float Speed = GetVelocity().Size();

	// ★ 速度で移動判定（しきい値 10 はお好みで）
	bIsMoving = (Speed > 10.0f);

	// ★ 足音処理
	if (bIsMoving && FootstepSound)
	{
		FootstepTimer += DeltaTime;

		if (FootstepTimer >= FootstepInterval)
		{
			UGameplayStatics::PlaySoundAtLocation(
				GetWorld(),          // ← ここを this ではなく GetWorld() に修正
				FootstepSound,
				GetActorLocation()
			);

			FootstepTimer = 0.0f;
		}
	}

	// ★ カメラ揺れ（元の機能）
	if (bIsShaking && CameraBoom)
	{
		ShakeTimer += DeltaTime;
		float Alpha = ShakeTimer / ShakeDuration;

		float CurrentIntensity = ShakeIntensity * (1.0f - Alpha);
		if (CurrentIntensity <= 0.0f)
		{
			bIsShaking = false;
			return;
		}

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

	// ★ 移動しているか判定（足音に使用）
	

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
