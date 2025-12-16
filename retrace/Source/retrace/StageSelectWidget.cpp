#include "StageSelectWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UStageSelectWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // ‰Šú‰»ˆ—‚ð‘‚­
    Title->OnClicked.AddUniqueDynamic(this, &UStageSelectWidget::OnButtonTitle);

    Stage1->OnClicked.AddUniqueDynamic(this, &UStageSelectWidget::OnButtonStage1);
    Stage2->OnClicked.AddUniqueDynamic(this, &UStageSelectWidget::OnButtonStage2);
    Stage3->OnClicked.AddUniqueDynamic(this, &UStageSelectWidget::OnButtonStage3);
}

void UStageSelectWidget::OnButtonTitle()
{
    UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("Title")));
}

void UStageSelectWidget::OnButtonStage1()
{
    UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("Stage1")));
}

void UStageSelectWidget::OnButtonStage2()
{
    UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("Stage2")));
}

void UStageSelectWidget::OnButtonStage3()
{
    UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("Stage3")));
}
