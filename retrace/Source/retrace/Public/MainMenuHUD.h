// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class RETRACE_API AMainMenuHUD : public AHUD
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
