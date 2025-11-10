#include "MonsterEffectManager.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraShakeBase.h"

AMonsterEffectManager::AMonsterEffectManager()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AMonsterEffectManager::BeginPlay()
{
    Super::BeginPlay();

    // PostProcessVolumeを自動取得
    if (!PostProcessVolume)
    {
        PostProcessVolume = Cast<APostProcessVolume>(
            UGameplayStatics::GetActorOfClass(GetWorld(), APostProcessVolume::StaticClass())
        );
    }

    if (PostProcessVolume)
    {
        PostProcessVolume->bUnbound = true; // 全画面に適用
    }
}
//void AMonsterEffectManager::Tick(float DeltaTime)
//{
//    Super::Tick(DeltaTime);
//
//    if (!Player || !Monster) return;
//
//    float Distance = FVector::Dist(Player->GetActorLocation(), Monster->GetActorLocation());
//    float MaxDistance = 1000.f; // 調整可能
//    float Intensity = FMath::Clamp(1.f - (Distance / MaxDistance), 0.f, 1.f);
//
//    if (Intensity > 0.f)
//    {
//        ApplyEffect(Intensity);
//    }
//    else
//    {
//        ClearEffect();
//    }
//}

void AMonsterEffectManager::ApplyEffect(float Intensity)
{
    if (!PostProcessVolume) return;

    CurrentIntensity = FMath::Clamp(Intensity, 0.f, 1.f);

    // 赤みを出す（SceneColorTintで）
    FPostProcessSettings& Settings = PostProcessVolume->Settings;
    Settings.bOverride_SceneFringeIntensity = true;
    Settings.bOverride_VignetteIntensity = true;
    Settings.bOverride_SceneColorTint = true;

    Settings.VignetteIntensity = FMath::Lerp(0.3f, 1.2f, CurrentIntensity);
    Settings.SceneColorTint = FLinearColor(1.0f, 1.0f - 0.6f * CurrentIntensity, 1.0f - 0.6f * CurrentIntensity);

    // カメラシェイクを適用
    if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
    {
        if (CameraShakeClass)
        {
            PC->ClientStartCameraShake(CameraShakeClass, CurrentIntensity);
        }
    }
}

void AMonsterEffectManager::ClearEffect()
{
    if (!PostProcessVolume) return;
    PostProcessVolume->Settings.VignetteIntensity = 0.3f;
    PostProcessVolume->Settings.SceneColorTint = FLinearColor::White;
    CurrentIntensity = 0.f;
}
