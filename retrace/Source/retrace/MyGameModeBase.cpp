// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMyGameModeBase::AMyGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn>PlayerPawnBPClass(TEXT("/Game/BPMyCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

