#include "MonsterEffectManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Engine/PostProcessVolume.h"

AMonsterEffectManager::AMonsterEffectManager()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AMonsterEffectManager::BeginPlay()
{
    Super::BeginPlay();

    PostProcessVolume = Cast<APostProcessVolume>(
        UGameplayStatics::GetActorOfClass(GetWorld(), APostProcessVolume::StaticClass())
    );

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
        return;
    }

    if (PlayerRef && MonsterRef && PostProcessVolume)
    {
        UpdateEffect(DeltaTime);
    }
}

void AMonsterEffectManager::UpdateEffect(float DeltaTime)
{
    const float Distance = FVector::Dist(
        PlayerRef->GetActorLocation(),
        MonsterRef->GetActorLocation()
    );

    HandleProximitySE(Distance);
    HandlePostProcess(Distance);
}

// ===== 距離SE =====
void AMonsterEffectManager::HandleProximitySE(float Distance)
{
    if (!ProximitySE) return;

    if (Distance <= ProximitySEDistance)
    {
        // 外 → 中 に入った瞬間だけ鳴らす
        if (!bIsPlayerInsideSEArea)
        {
            UGameplayStatics::PlaySound2D(this, ProximitySE);
            bIsPlayerInsideSEArea = true;
        }
    }
    else
    {
        // 一度離れたらリセット
        bIsPlayerInsideSEArea = false;
    }
}

// ===== ポストプロセス =====
void AMonsterEffectManager::HandlePostProcess(float Distance)
{
    const float Intensity = FMath::Clamp(
        1.f - Distance / EffectStartDistance,
        0.f,
        1.f
    );

    FPostProcessSettings& Settings = PostProcessVolume->Settings;

    Settings.bOverride_VignetteIntensity = true;
    Settings.bOverride_SceneColorTint = true;

    Settings.VignetteIntensity = FMath::Lerp(0.3f, 2.5f, Intensity);
    Settings.SceneColorTint =
        FLinearColor(1.f, 1.f - 0.6f * Intensity, 1.f - 0.6f * Intensity);
}

// ===== 死亡フェード =====
void AMonsterEffectManager::StartDeathFade()
{
    bIsDying = true;
    DeathFadeAlpha = 0.f;
}

void AMonsterEffectManager::UpdateDeathFade(float DeltaTime)
{
    DeathFadeAlpha += DeltaTime / DeathFadeDuration;

    const float Fade = FMath::Clamp(DeathFadeAlpha, 0.f, 1.f);

    if (PostProcessVolume)
    {
        PostProcessVolume->Settings.bOverride_SceneColorTint = true;
        PostProcessVolume->Settings.SceneColorTint =
            FMath::Lerp(FLinearColor::White, FLinearColor::Black, Fade);
    }

    if (DeathFadeAlpha >= 1.f)
    {
        OnDeathFadeFinished();
    }
}

void AMonsterEffectManager::OnDeathFadeFinished()
{
    bIsDying = false;
    OnDeathFadeFinishedEvent.Broadcast();
}

void AMonsterEffectManager::ResetDeathState()
{
    bIsDying = false;
    DeathFadeAlpha = 0.f;

    if (PostProcessVolume)
    {
        FPostProcessSettings& Settings = PostProcessVolume->Settings;

        Settings.bOverride_SceneColorTint = false;
        Settings.bOverride_VignetteIntensity = false;

        Settings.SceneColorTint = FLinearColor::White;
        Settings.VignetteIntensity = 0.3f;
    }
}
