#include "MonsterEffectManager.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraShakeBase.h"
#include "GameFramework/PlayerController.h"
#include "MyCharacter.h"
#include "MovingMonster.h"
#include "Engine/PostProcessVolume.h"

AMonsterEffectManager::AMonsterEffectManager()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AMonsterEffectManager::BeginPlay()
{
    Super::BeginPlay();

    // PostProcessVolume を取得
    PostProcessVolume = Cast<APostProcessVolume>(
        UGameplayStatics::GetActorOfClass(GetWorld(), APostProcessVolume::StaticClass())
    );
    if (PostProcessVolume)
    {
        PostProcessVolume->bUnbound = true;
    }
}

void AMonsterEffectManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Player がまだ存在していなければ取得
    if (!Player)
    {
        Player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
        if (!Player) return; // まだいない場合は終了
    }

    // Monster がまだセットされていなければ取得
    if (!Monster)
    {
        Monster = Cast<AMovingMonster>(UGameplayStatics::GetActorOfClass(GetWorld(), AMovingMonster::StaticClass()));
        if (!Monster) return; // まだいない場合は終了
    }

    // 距離計算
    float Distance = FVector::Dist(Player->GetActorLocation(), Monster->GetActorLocation());
    float Intensity = FMath::Clamp(1.0f - (Distance / MaxDistance), 0.f, 1.f);

    ApplyEffect(Intensity);
}

void AMonsterEffectManager::ApplyEffect(float Intensity)
{
    if (!PostProcessVolume) return;

    CurrentIntensity = Intensity;

    FPostProcessSettings& Settings = PostProcessVolume->Settings;
    Settings.bOverride_VignetteIntensity = true;
    Settings.VignetteIntensity = FMath::Lerp(0.3f, 1.2f, CurrentIntensity);

    Settings.bOverride_SceneColorTint = true;
    Settings.SceneColorTint = FLinearColor(1.0f, 1.0f - 0.6f * CurrentIntensity, 1.0f - 0.6f * CurrentIntensity);

    // カメラシェイクを入れる場合
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
