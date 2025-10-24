#include "MonsterSpawnTrigger.h"
#include "Components/BoxComponent.h"
#include "MovingMonster.h"
#include "SpawnPointActor.h"

AMonsterSpawnTrigger::AMonsterSpawnTrigger()
{
    PrimaryActorTick.bCanEverTick = false;

    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    RootComponent = TriggerBox;

    TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
}

void AMonsterSpawnTrigger::BeginPlay()
{
    Super::BeginPlay();

    TriggerBox->OnComponentBeginOverlap.AddDynamic(
        this,
        &AMonsterSpawnTrigger::OnOverlapBegin
    );
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
    // SpawnPoint が指定されていない場合は終了
    if (!SpawnPoint || !MonsterClass) return;

    FActorSpawnParameters Params;

    // ★ SpawnPoint の座標＆角度でスポーン！
    FTransform SpawnTransform = SpawnPoint->GetActorTransform();

    AMovingMonster* Monster = GetWorld()->SpawnActor<AMovingMonster>(
        MonsterClass,
        SpawnTransform,
        Params
    );

    if (Monster)
    {
        Monster->ActivateMonster();
    }

    // 条件に応じて一回きりなら破壊
    // Destroy();
}
