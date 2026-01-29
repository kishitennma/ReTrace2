#include "AudioManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

AAudioManager::AAudioManager()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AAudioManager::BeginPlay()
{
    Super::BeginPlay();
}

void AAudioManager::PlayBGM(USoundBase* NewBGM)
{
    if (!NewBGM) return;

    if (BGMComponent)
    {
        BGMComponent->Stop();
    }

    BGMComponent = UGameplayStatics::SpawnSound2D(
        this,
        NewBGM,
        1.f,
        1.f,
        0.f,
        nullptr,
        true
    );
}
