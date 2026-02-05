// Fill out your copyright notice in the Description page of Project Settings.


#include "BGMActor.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"
#include "SoundGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABGMActor::ABGMActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// コンストラクタ
	BGMComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BGMComponent"));
	BGMComponent->SetupAttachment(RootComponent);
	BGMComponent->bAutoActivate = false; // 自動再生しない


}

// Called when the game starts or when spawned
void ABGMActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABGMActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    CheckAndPlayMonsterBGM();
    BGMstop();
}

void ABGMActor::CheckAndPlayMonsterBGM()
{
    USoundGameInstance* GI =
        Cast<USoundGameInstance>(UGameplayStatics::GetGameInstance(this));
    if (!GI)return;

    if (GI->bShouldPlayBGM && BGM)
    {
        if (!BGMComponent->IsPlaying())
        {
            BGMComponent->SetSound(BGM);
            BGMComponent->Play();
        }
    }
    else
    {
        // フラグがオフなら止める
        if (BGMComponent->IsPlaying())
        {
            BGMComponent->Stop();
        }
    }
}

void ABGMActor::BGMstop()
{
    USoundGameInstance* GI =
        Cast<USoundGameInstance>(UGameplayStatics::GetGameInstance(this));
    if (!GI)return;

    if (!GI->bShouldPlayBGM)
    {
        // フラグがオフなら止める
        if (BGMComponent->IsPlaying())
        {
            BGMComponent->Stop();
        }
    }
}

