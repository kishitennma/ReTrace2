// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StageSelectWidget.generated.h"

class UButton;

UCLASS()
class RETRACE_API UStageSelectWidget : public UUserWidget
{
    GENERATED_BODY()

public:

    // ブループリントから呼べる関数
    UFUNCTION(BlueprintCallable)
    void LoadStage(FName StageName);

    void NativeConstruct() override;
private:
   
  /*  UPROPERTY(meta = (BindWidget))
    class UButton* Stage1;
    UPROPERTY(meta = (BindWidget))
    class UButton* Stage2;
    UPROPERTY(meta = (BindWidget))
    class UButton* Stage3;
    UPROPERTY(meta = (BindWidget))
    class UButton* Title;*/
};
