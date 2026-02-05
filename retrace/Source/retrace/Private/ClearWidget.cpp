// Fill out your copyright notice in the Description page of Project Settings.


#include "ClearWidget.h"
#include "Components/Button.h"
#include "SoundGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UClearWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // ‰Šú‰»ˆ—‚ð‘‚­
    Title->OnClicked.AddUniqueDynamic(this, &UClearWidget::OnButtonTitle);
    StageSelect->OnClicked.AddUniqueDynamic(this, &UClearWidget::OnButtonStageSelect);

}

void UClearWidget::OnButtonTitle()
{
    if (GI)
        GI->PlayUISound(clicksound);
    GI->bShouldPlayBGM = false;

    UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("Title")));
}

void UClearWidget::OnButtonStageSelect()
{

    if (GI)
        GI->PlayUISound(clicksound);
    GI->bShouldPlayBGM = false;
    UE_LOG(LogTemp, Warning, TEXT("stageselect"));
    UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("stageselect")));
   
}