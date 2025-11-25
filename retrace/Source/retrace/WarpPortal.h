#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "WarpPortal.generated.h"

class UBoxComponent;
class UNiagaraComponent; // 任意（エフェクト使う場合）

UCLASS()
class RETRACE_API AWarpPortal : public AActor
{
    GENERATED_BODY()

public:
    AWarpPortal();

protected:
    virtual void BeginPlay() override;

private:

    // 触れた判定
    UPROPERTY(VisibleAnywhere)
    UBoxComponent* TriggerBox;

    // ワープ先（レベル内の別の WarpPortal Actor を指定する）
    UPROPERTY(EditAnywhere, Category = "Warp")
    AWarpPortal* TargetPortal;

    UPROPERTY(VisibleAnywhere, Category = "Warp")
    UNiagaraComponent* PortalEffect;

    UPROPERTY(EditAnywhere, Category = "Warp")
    UNiagaraSystem* PortalEffectAsset;   


    // ワープ直後再発動防止
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

public:
    FORCEINLINE AWarpPortal* GetTargetPortal() const { return TargetPortal; }
};
