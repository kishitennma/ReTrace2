// MyCharacter.cpp

#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputActionValue.h"
#include "SoundGameInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/UserWidget.h"

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

	if (USoundGameInstance* GI =
		Cast<USoundGameInstance>(GetGameInstance()))
	{
		GI->StopBGM();
	}

	DefaultDistance = CameraBoom->TargetArmLength;
	DefaultAngle = CameraBoom->GetRelativeRotation();
	DefaultOffset = CameraBoom->SocketOffset;


	// MonsterEffectManager を取得
	MonsterEffectManager = Cast<AMonsterEffectManager>(
		UGameplayStatics::GetActorOfClass(
			GetWorld(),
			AMonsterEffectManager::StaticClass()
		)
	);

	if (MonsterEffectManager)
	{
		MonsterEffectManager->OnDeathFadeFinishedEvent.AddDynamic(
			this,
			&AMyCharacter::OnDeathFadeFinished
		);
	}
}




void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float Speed = GetVelocity().Size();

	// ★ 速度で移動判定（しきい値 10 はお好みで）
	bIsMoving = (Speed > 10.0f);

	// ★ 足音処理
	//if (bIsMoving && FootstepSound)
	//{
	//	FootstepTimer += DeltaTime;

	//	if (FootstepTimer >= FootstepInterval)
	//	{
	//		UGameplayStatics::PlaySoundAtLocation(
	//			GetWorld(),          // ← ここを this ではなく GetWorld() に修正
	//			FootstepSound,
	//			GetActorLocation()
	//		);

	//		FootstepTimer = 0.0f;
	//	}
	//}

	// ★ カメラ揺れ（元の機能）
	if (bIsShaking && CameraBoom)
	{
		ShakeTimer += DeltaTime;
		float Alpha = ShakeTimer / ShakeDuration;
		UGameplayStatics::PlaySoundAtLocation(
						GetWorld(),          // ← ここを this ではなく GetWorld() に修正
				gogogosound,
				GetActorLocation()
				);
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

void AMyCharacter::PlayKnockDown()
{
	if (!KnockDownMontage) return;

	// すでに倒れてたら再生しない
	if (GetCharacterMovement()->IsFalling() == false &&
		GetCharacterMovement()->MovementMode == MOVE_None)
	{
		return;
	}

	// 移動停止
	GetCharacterMovement()->DisableMovement();
	MonsterEffectManager = Cast<AMonsterEffectManager>(
		UGameplayStatics::GetActorOfClass(
			GetWorld(),
			AMonsterEffectManager::StaticClass()));

	if (MonsterEffectManager)
	{
		MonsterEffectManager->StartDeathFade();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("MonsterEffectManager is NULL"));
	}
	;

	// 向き固定（任意）
	bUseControllerRotationYaw = false;
	if (Knock)
	{
		UGameplayStatics::PlaySoundAtLocation(
			GetWorld(),
			Knock,
			GetActorLocation()
		);
	}
	// モンタージュ再生
	if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
	{
		AnimInstance->Montage_Play(KnockDownMontage);
	}
}

void AMyCharacter::OnDeathFadeFinished()
{
	UE_LOG(LogTemp, Warning, TEXT("MyCharacter received death fade"));

	if (!DeathWidgetClass) return;

	if (!DeathWidget)
	{
		DeathWidget = CreateWidget<UUserWidget>(
			GetWorld(),
			DeathWidgetClass
		);
	}

	
		if (DeathWidget && !DeathWidget->IsInViewport())
		{
			DeathWidget->AddToViewport();

			// 入力をUIに
			if (APlayerController* PC = Cast<APlayerController>(GetController()))
			{
				PC->SetInputMode(FInputModeUIOnly());
				PC->bShowMouseCursor = true;
			}
		}

		
	
}

void AMyCharacter::Retry()
{
	if (MonsterEffectManager)
	{
		MonsterEffectManager->ResetDeathState();
	}
	USoundGameInstance* GI =
		Cast<USoundGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (!GI)return;
	GI->bShouldPlayBGM = false;
	// 入力モードを戻す
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		PC->SetInputMode(FInputModeGameOnly());
		PC->bShowMouseCursor = false;

		// EnhancedInput 再登録
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	// 移動復活
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);

	if (DeathWidget)
	{
		DeathWidget->RemoveFromParent();
	}

	// レベルリロード
	UGameplayStatics::OpenLevel(
		this,
		FName(*UGameplayStatics::GetCurrentLevelName(this))
	);
}

void AMyCharacter::PlayClearWhidget()
{
	if (!ClearWidgetClass) return;

	if (!ClearWidget)
	{
		ClearWidget = CreateWidget<UUserWidget>(
			GetWorld(),
			ClearWidgetClass
		);
	}
	USoundGameInstance* GI =
		Cast<USoundGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (!GI)return;
	GI->bShouldPlayBGM = false;
	
	if (clear)
	{
		UGameplayStatics::PlaySoundAtLocation(
			GetWorld(),
			clear,
			GetActorLocation()
		);
	}

	if (ClearWidget && !ClearWidget->IsInViewport())
	{
		ClearWidget->AddToViewport();

		// 入力をUIに
		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			PC->SetInputMode(FInputModeUIOnly());
			PC->bShowMouseCursor = true;
		}
	}
}

void AMyCharacter::PlayerGoal()
{
	//移動停止
	GetCharacterMovement()->DisableMovement();
	MonsterEffectManager = Cast<AMonsterEffectManager>(
		UGameplayStatics::GetActorOfClass(
			GetWorld(),
			AMonsterEffectManager::StaticClass()));
}

void AMyCharacter::ApplyClearCamera(
	FRotator CameraRotation,
	float CameraDistance,
	FVector CameraOffset
)
{
	if (!CameraBoom) return;

	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->SetWorldRotation(CameraRotation);
	CameraBoom->TargetArmLength = CameraDistance;
	CameraBoom->SetRelativeLocation(CameraOffset);
}

void AMyCharacter::ApplyDeathCamera(
	FRotator CameraRotation,
	float CameraDistance,
	FVector CameraOffset
)
{
	if (!CameraBoom) return;

	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->SetWorldRotation(CameraRotation);
	CameraBoom->TargetArmLength = CameraDistance;
	CameraBoom->SetRelativeLocation(CameraOffset);
}


