#include "MonsterEffectManager.h"
#include "Engine/PostProcessVolume.h"

void AMonsterEffectManager::ApplyEffect(float Intensity)
{
    if (!TargetPostProcess) return;

    auto& Settings = TargetPostProcess->Settings;

    // 赤み
    Settings.bOverride_ColorSaturation = true;
    Settings.ColorSaturation = FVector4(1.0f, 1.0f - Intensity * 0.5f, 1.0f - Intensity * 0.5f, 1.0f);

    // ビネット（画面周囲の暗化）
    Settings.bOverride_VignetteIntensity = true;
    Settings.VignetteIntensity = Intensity * 0.8f;

    // フリンジ（若干のブラー）
    Settings.bOverride_SceneFringeIntensity = true;
    Settings.SceneFringeIntensity = Intensity * 2.0f;
}

void AMonsterEffectManager::ClearEffect()
{
    if (!TargetPostProcess) return;

    auto& Settings = TargetPostProcess->Settings;
    Settings.VignetteIntensity = 0.0f;
    Settings.SceneFringeIntensity = 0.0f;
    Settings.ColorSaturation = FVector4(1, 1, 1, 1);
}
