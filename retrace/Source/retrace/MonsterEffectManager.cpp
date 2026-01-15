#include "MonsterEffectManager.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "Engine/PostProcessVolume.h"

AMonsterEffectManager::AMonsterEffectManager()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AMonsterEffectManager::BeginPlay()
{
    Super::BeginPlay();

    if (!PostProcessVolume)
    {
        PostProcessVolume = Cast<APostProcessVolume>(
            UGameplayStatics::GetActorOfClass(GetWorld(), APostProcessVolume::StaticClass())
        );
    }

    if (PostProcessVolume)
    {
        PostProcessVolume->bUnbound = true;
    }
}

void AMonsterEffectManager::SetTargets(ACharacter* Player, AActor* Monster)
{
    PlayerRef = Player;
    MonsterRef = Monster;
}

void AMonsterEffectManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bIsDying)
    {
        UpdateDeathFade(DeltaTime);
        return; // ← 距離演出を止める
    }

    // 毎フレーム距離をチェック！
    if (PlayerRef && MonsterRef && !bIsDying)
    {
        UpdateEffect(PlayerRef, MonsterRef);
    }
}

void AMonsterEffectManager::UpdateEffect(ACharacter* Player, AActor* Monster)
{
    if (!Player || !Monster || !PostProcessVolume) return;

    float Distance = FVector::Dist(Player->GetActorLocation(), Monster->GetActorLocation());
    float Intensity = FMath::Clamp(1.f - Distance / 1000.f, 0.f, 1.f);

    FPostProcessSettings& Settings = PostProcessVolume->Settings;

    Settings.bOverride_VignetteIntensity = true;
    Settings.bOverride_SceneColorTint = true;

    Settings.VignetteIntensity = FMath::Lerp(0.3f, 2.5f, Intensity);
    Settings.SceneColorTint = FLinearColor(1.f, 1.f - 0.6f * Intensity, 1.f - 0.6f * Intensity);
}

void AMonsterEffectManager::StartDeathFade()
{
    bIsDying = true;
    DeathFadeAlpha = 0.0f;
}

void AMonsterEffectManager::UpdateDeathFade(float DeltaTime)
{
    if (bIsDying && PostProcessVolume)
    {
        DeathFadeAlpha += DeltaTime / DeathFadeDuration;

        float Fade = FMath::Clamp(DeathFadeAlpha, 0.f, 1.f);

        PostProcessVolume->Settings.bOverride_SceneColorTint = true;
        PostProcessVolume->Settings.SceneColorTint =
            FMath::Lerp(FLinearColor::White, FLinearColor::Black, Fade);


        // ★ 完了判定
        if (DeathFadeAlpha >= 1.0f)
        {
            DeathFadeAlpha = 1.0f;
          
            OnDeathFadeFinished();   
        }
    }

}

void AMonsterEffectManager::OnDeathFadeFinished()
{
    UE_LOG(LogTemp, Warning, TEXT("Death Fade Finished"));
    OnDeathFadeFinishedEvent.Broadcast(); 
}

