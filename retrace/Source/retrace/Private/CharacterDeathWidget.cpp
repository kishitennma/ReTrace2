


#include "CharacterDeathWidget.h"
#include "Components/Button.h"
#include "SoundGameInstance.h"
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
    if (GI)
        GI->PlayUISound(clicksound);

    if (AMyCharacter* Player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)))
    {
        Player->Retry();
    }
}

void UCharacterDeathWidget::OnButtonStageSelect()
{

    if (GI)
        GI->PlayUISound(clicksound);
    GI->bShouldPlayBGM = false;
    UE_LOG(LogTemp, Warning, TEXT("StageSlect"));
    UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("stageselect")));
}