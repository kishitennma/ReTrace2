// Fill out your copyright notice in the Description page of Project Settings.


#include "StageSelectWidget.h"
#include "Kismet/GameplayStatics.h"

void UStageSelectWidget::LoadStage(FName StageName)
{
    if (StageName != NAME_None)
    {
        UGameplayStatics::OpenLevel(GetWorld(), StageName);
    }
}



