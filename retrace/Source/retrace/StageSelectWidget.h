#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StageSelectWidget.generated.h"

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
