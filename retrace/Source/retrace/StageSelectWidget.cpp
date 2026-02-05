#include "StageSelectWidget.h"
#include "Components/Button.h"
#include "SoundGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UStageSelectWidget::NativeConstruct()
{
    Super::NativeConstruct();
    GI= Cast<USoundGameInstance>(GetGameInstance());
    if (GI)
    {
        GI->PlayBGM(TitleBGM); // “¯‚¶BGM‚È‚çÄÄ¶‚³‚ê‚È‚¢
    }
    // ‰Šú‰»ˆ—‚ð‘‚­
    Title->OnClicked.AddUniqueDynamic(this, &UStageSelectWidget::OnButtonTitle);

    Stage1->OnClicked.AddUniqueDynamic(this, &UStageSelectWidget::OnButtonStage1);
    Stage2->OnClicked.AddUniqueDynamic(this, &UStageSelectWidget::OnButtonStage2);
    Stage3->OnClicked.AddUniqueDynamic(this, &UStageSelectWidget::OnButtonStage3);
}

void UStageSelectWidget::OnButtonTitle()
{
    if (GI)
        GI->PlayUISound(clicksound);
    UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("Title")));
}

void UStageSelectWidget::OnButtonStage1()
{
    if (GI)
        GI->PlayUISound(startsound);
    UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("Stage1")));
}

void UStageSelectWidget::OnButtonStage2()
{
    if (GI)
        GI->PlayUISound(startsound);
    UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("Stage2")));
}

void UStageSelectWidget::OnButtonStage3()
{
    if (GI)
        GI->PlayUISound(startsound);
    UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("Stage3")));
}
