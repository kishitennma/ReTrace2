// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CharacterDeathHUD.generated.h"

/**
 * 
 */
UCLASS()
class RETRACE_API ACharacterDeathHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	UPROPERTY()
	UUserWidget* UserWidget;
	UPROPERTY()
	APlayerController* PlayerController;
	UPROPERTY(EditAnywhere, category = "UI")
	TSubclassOf<UUserWidget> WidgetClass;
	
};
