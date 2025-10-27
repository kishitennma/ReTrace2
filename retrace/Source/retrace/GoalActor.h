// GoalActor.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GoalActor.generated.h"

UCLASS()
class RETRACE_API AGoalActor : public AActor
{
    GENERATED_BODY()

public:
    AGoalActor();

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    class UStaticMeshComponent* Mesh;

};
