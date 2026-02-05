// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class USoundGameInstance;

class UButton;
/**
 * 
 */
UCLASS()
class RETRACE_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	void NativeConstruct() override;
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ButtonPlay;

	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonQuit;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* clicksound;
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* TitleBGM;
	UPROPERTY()
	USoundGameInstance* GI;

	UFUNCTION()
	void OnButtonPlayClicked();

	UFUNCTION()
	void OnButtonQuitClicked();
	
};
