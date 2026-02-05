// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "SoundGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	GI =
		Cast<USoundGameInstance>(GetGameInstance());
	if (GI)
	{
		GI->PlayBGM(TitleBGM);
	}
	ButtonPlay->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OnButtonPlayClicked);

	// ButtonQuitのOnClickedに「OnButtonQuitClicked」を関連づける
	ButtonQuit->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OnButtonQuitClicked);
}

void UMainMenuWidget::OnButtonPlayClicked()
{
	// GameInstanceの変数を初期化する
	
	if (GI)
		GI->PlayUISound(clicksound);

	// Level01をLoadする
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("stageselect")));

}

void UMainMenuWidget::OnButtonQuitClicked()
{
	if (GI)
		GI->PlayUISound(clicksound);

	// PlayerControllerを取得する
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		// ゲームを終了する
		UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, false);
	}
}