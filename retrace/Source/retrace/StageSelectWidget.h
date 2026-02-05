#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StageSelectWidget.generated.h"

class USoundGameInstance;

class UButton;

UCLASS()
class RETRACE_API UStageSelectWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> Title;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> Stage1;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> Stage2;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> Stage3;

    UPROPERTY(EditAnywhere, Category = "Sound")
    USoundBase* clicksound;
    UPROPERTY(EditAnywhere, Category = "Sound")
    USoundBase* startsound;
    UPROPERTY(EditAnywhere, Category = "Sound")
    USoundBase* TitleBGM;
    UPROPERTY()
    USoundGameInstance* GI;

private:
    UFUNCTION()
    void OnButtonStage1();

    UFUNCTION()
    void OnButtonTitle();

    UFUNCTION()
    void OnButtonStage2();

    UFUNCTION()
    void OnButtonStage3();
};
