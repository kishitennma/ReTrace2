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
    if (!OtherActor) return;
    // --- Spawn transform を SpawnPoint から取得 ---
    FTransform SpawnTransform = SpawnPoint->GetActorTransform();

    // SpawnParameters（必要ならオプションを設定）
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    // モンスターをスポーン
    AMovingMonster* SpawnedMonster = GetWorld()->SpawnActor<AMovingMonster>(MonsterClass, SpawnTransform, SpawnParams);
    if (SpawnedMonster)
    {
        SpawnedMonster->ActivateMonster(); // 既存メソッド
    }

    if (GoalClass && GoalSpawnPoint)
    {
        FTransform GoalTransform = GoalSpawnPoint->GetActorTransform();

        AGoalActor* SpawnedGoal = GetWorld()->SpawnActor<AGoalActor>(
            GoalClass, GoalTransform
        );

        if (SpawnedGoal)
        {
            UE_LOG(LogTemp, Warning, TEXT("Goal Actor Spawned!"));
        }
    }

    // --- プレイヤー取得 ---
    ACharacter* PlayerChar = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    // または OtherActor がプレイヤーなら:
    // ACharacter* PlayerChar = Cast<ACharacter>(OtherActor);

   
    AMonsterEffectManager* EffectManager = Cast<AMonsterEffectManager>(
        UGameplayStatics::GetActorOfClass(GetWorld(), AMonsterEffectManager::StaticClass())
    );
    // --- EffectManager があればターゲットを渡す ---
    if (EffectManager && PlayerChar && SpawnedMonster)
    {
        EffectManager->SetTargets(PlayerChar, SpawnedMonster);
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



