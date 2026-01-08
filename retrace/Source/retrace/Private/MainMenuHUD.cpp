// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/UserWidget.h"


void AMainMenuHUD::BeginPlay()
{
	// WidgetBlueprint‚ÌClass‚ðŽæ“¾‚·‚é
	FString Path = TEXT("/Game/BPW_MainMenuWidget.BPW_MainMenuWidget_C");
	WidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(*Path)).LoadSynchronous();

	// PlayerController‚ðŽæ“¾‚·‚é
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	// WidgetClass‚ÆPlayerController‚ªŽæ“¾‚Å‚«‚½‚©”»’è‚·‚é
	if (WidgetClass && PlayerController)
	{
		// Widget‚ðì¬‚·‚é
		 UserWidget = UWidgetBlueprintLibrary::Create(GetWorld(), WidgetClass, PlayerController);
	
		// Viewport‚É’Ç‰Á‚·‚é
		UserWidget->AddToViewport(0);

		// MouseCursor‚ð•\Ž¦‚·‚é
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PlayerController, UserWidget, EMouseLockMode::DoNotLock, true, false);
		PlayerController->SetShowMouseCursor(true);
	}
}