#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "GoalActor.generated.h"



UCLASS()
class RETRACE_API AGoalActor : public AActor
{
    GENERATED_BODY()

public:
    AGoalActor();

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnOverlapBegin(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
    FVector NewCameraOffset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
    FRotator NewCameraRotation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Change")
    float NewCameraDistance;

public:
    UPROPERTY(VisibleAnywhere)
    class UBoxComponent* CollisionBox;

   
   virtual void Tick(float DeltaTime) override;

   


    bool HasActive = false;
};
