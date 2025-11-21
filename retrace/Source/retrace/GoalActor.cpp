#include "GoalActor.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"


AGoalActor::AGoalActor()
{
    PrimaryActorTick.bCanEverTick = false;

    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    RootComponent = CollisionBox;

    CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionBox->SetCollisionResponseToAllChannels(ECR_Overlap);

    CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AGoalActor::OnOverlapBegin);
}

void AGoalActor::BeginPlay()
{
    Super::BeginPlay();
}


void AGoalActor::Tick(float deltatime)
{
    Super::Tick(deltatime);
}

void AGoalActor::OnOverlapBegin(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult
)
{
    if (!Cast<ACharacter>(OtherActor)) return;
    if (HasActive) return;
    if (ClearWidgetClass)
    {
        UUserWidget* ClearWidget = CreateWidget<UUserWidget>(GetWorld(), ClearWidgetClass);
        if (ClearWidget)
        {
            ClearWidget->AddToViewport();
            HasActive = true;
           

        }
    }
}
