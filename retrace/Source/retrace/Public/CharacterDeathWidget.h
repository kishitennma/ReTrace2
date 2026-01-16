// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "retrace/MyCharacter.h"
#include "CharacterDeathWidget.generated.h"


class UButton;
/**
 * 
 */
UCLASS()
class RETRACE_API UCharacterDeathWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Retry;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> StageSelect;

private:
	UFUNCTION()
	void OnButtonRetry();

	UFUNCTION()
	void OnButtonStageSelect();
	
};
