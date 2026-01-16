


#include "CharacterDeathWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UCharacterDeathWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // ‰Šú‰»ˆ—‚ð‘‚­
    Retry->OnClicked.AddUniqueDynamic(this, &UCharacterDeathWidget::OnButtonRetry);
    StageSelect->OnClicked.AddUniqueDynamic(this, &UCharacterDeathWidget::OnButtonStageSelect);
    
}

void UCharacterDeathWidget:: OnButtonRetry()
{
    UGameplayStatics::OpenLevel(
        this,
        FName(*GetWorld()->GetName()));
}

void UCharacterDeathWidget::OnButtonStageSelect()
{
    UE_LOG(LogTemp, Warning, TEXT("StageSlect"));
    UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("stageselect")));
}