// GoalActor.cpp
#include "GoalActor.h"
#include "Components/StaticMeshComponent.h"

AGoalActor::AGoalActor()
{
    PrimaryActorTick.bCanEverTick = false;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;
}

void AGoalActor::BeginPlay()
{
    Super::BeginPlay();
}
