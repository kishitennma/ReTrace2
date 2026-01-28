// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "retrace/MyCharacter.h"
#include "ClearWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class RETRACE_API UClearWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Title;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> StageSelect;

private:
	UFUNCTION()
	void OnButtonTitle();

	UFUNCTION()
	void OnButtonStageSelect();

	
};
