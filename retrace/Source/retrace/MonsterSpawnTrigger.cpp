#include "MonsterSpawnTrigger.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

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

    FVector Location = SpawnPoint->GetActorLocation();
    FRotator Rotation = SpawnPoint->GetActorRotation();

    AMovingMonster* Monster = GetWorld()->SpawnActor<AMovingMonster>(MonsterClass, Location, Rotation);

    if (Monster)
    {
        Monster->ActivateMonster();
    }

    bHasSpawned = true;
}

