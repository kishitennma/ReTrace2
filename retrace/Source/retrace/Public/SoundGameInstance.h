// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "SoundGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class RETRACE_API USoundGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void PlayUISound(USoundBase* Sound)
	{
		if (Sound)
		{
			UGameplayStatics::PlaySound2D(this, Sound);
		}
	}

	UPROPERTY()
	bool bShouldPlayBGM = false;

	UPROPERTY()
	UAudioComponent* BGMComponent;

	UPROPERTY()
	USoundBase* CurrentBGM;

	virtual void Init() override
	{
		UE_LOG(LogTemp, Warning, TEXT("SoundGameInstance Init called"));

		BGMComponent = NewObject<UAudioComponent>(this);
		BGMComponent->bAutoActivate = false;
		BGMComponent->bIsUISound = true;
		BGMComponent->RegisterComponent();
	}

	UFUNCTION(BlueprintCallable)
	void PlayBGM(USoundBase* NewBGM)
	{
		if (!NewBGM || NewBGM == CurrentBGM) return;

		UWorld* World = GetWorld();
		if (!World) return;

		if (BGMComponent)
		{
			BGMComponent->Stop();
		}

		BGMComponent = UGameplayStatics::SpawnSound2D(
			World,
			NewBGM,
			1.f,
			1.f,
			0.f,
			nullptr,
			true   // ← これが超重要（レベル遷移しても残る）
		);

		CurrentBGM = NewBGM;
	}

	UFUNCTION(BlueprintCallable)
	void StopBGM()
	{
		if (BGMComponent)
		{
			BGMComponent->Stop();
			CurrentBGM = nullptr;
		}
	}
};
