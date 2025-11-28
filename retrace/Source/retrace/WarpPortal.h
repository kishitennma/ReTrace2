#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "WarpPortal.generated.h"

class UBoxComponent;

UCLASS()
class RETRACE_API AWarpPortal : public AActor
{
    GENERATED_BODY()

public:
    AWarpPortal();

protected:
    virtual void OnConstruction(const FTransform& Transform) override;
    virtual void BeginPlay() override;

private:
    UPROPERTY(VisibleAnywhere)
    USceneComponent* Root;

    UPROPERTY(VisibleAnywhere)
    UBoxComponent* TriggerBox;

    UPROPERTY(VisibleAnywhere)
    UNiagaraComponent* PortalEffect;

    UPROPERTY(EditAnywhere, Category = "Warp")
    UNiagaraSystem* PortalEffectAsset;

    UPROPERTY(EditAnywhere, Category = "Warp")
    AWarpPortal* TargetPortal;

    bool bCanTeleport = true;

    UFUNCTION()
    void OnOverlapBegin(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );
};
