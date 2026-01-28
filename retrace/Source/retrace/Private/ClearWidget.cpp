// Fill out your copyright notice in the Description page of Project Settings.


#include "ClearWidget.h"
#include "Components/Button.h"
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
    UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("Title")));
}

void UClearWidget::OnButtonStageSelect()
{
    UE_LOG(LogTemp, Warning, TEXT("stageslect"));
   
}