#include "MonsterSpawnTrigger.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"


AMonsterSpawnTrigger::AMonsterSpawnTrigger()
{
    PrimaryActorTick.bCanEverTick = false;

    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    RootComponent = TriggerBox;

    TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    TriggerBox->SetCollisionResponseToAllChannels(ECR_Ignore);
    TriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AMonsterSpawnTrigger::BeginPlay()
{
    Super::BeginPlay();
    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AMonsterSpawnTrigger::OnOverlapBegin);
}

void AMonsterSpawnTrigger::OnOverlapBegin(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult
)
{
    if (bHasSpawned) return;
    if (!MonsterClass || !SpawnPoint) return;

    // SpawnPoint の位置と回転を取得
    FVector Location = SpawnPoint->GetActorLocation();
    FRotator Rotation = SpawnPoint->GetActorRotation();

    // モンスターを出現
    AMovingMonster* Monster = GetWorld()->SpawnActor<AMovingMonster>(MonsterClass, Location, Rotation);

    if (Monster)
    {
        Monster->ActivateMonster();

        AMonsterEffectManager* EffectManager = Cast<AMonsterEffectManager>(
            UGameplayStatics::GetActorOfClass(GetWorld(), AMonsterEffectManager::StaticClass()));

        // 例：MonsterSpawnTrigger.cpp の OnOverlapBegin の中で
        if (EffectManager == nullptr)
        {
            EffectManager = Cast<AMonsterEffectManager>(
                UGameplayStatics::GetActorOfClass(GetWorld(), AMonsterEffectManager::StaticClass())
            );
        }

        if (EffectManager)
        {
            EffectManager->ApplyEffect(1.0f);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("EffectManager is NULL!"));
        }
    }

    if (AMyCharacter* Player = Cast<AMyCharacter>(OtherActor))
    {
        // --- カメラをワールド回転モードにする ---
        Player->CameraBoom->SetUsingAbsoluteRotation(true);

        // ステージの固定方向を向かせる（たとえば少し俯瞰）
        Player->CameraBoom->SetWorldRotation(NewCameraRotation);

        // カメラ距離（ズーム距離）
        Player->CameraBoom->TargetArmLength = NewCameraDistance;

        // キャラ位置に対して固定オフセット（ローカル相対位置）
        Player->CameraBoom->SetRelativeLocation(NewCameraOffset);

        UE_LOG(LogTemp, Warning, TEXT("BP値確認: Offset=%s, Rotation=%s, Distance=%f"),
            *NewCameraOffset.ToString(),
            *NewCameraRotation.ToString(),
            NewCameraDistance);
    }

    bHasSpawned = true;
}



