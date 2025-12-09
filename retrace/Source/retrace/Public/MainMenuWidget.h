// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"


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

	UFUNCTION()
	void OnButtonPlayClicked();

	UFUNCTION()
	void OnButtonQuitClicked();
	
};
