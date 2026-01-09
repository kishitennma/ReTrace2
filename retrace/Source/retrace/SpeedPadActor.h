#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpeedPadActor.generated.h"

UCLASS()
class RETRACE_API ASpeedPadActor : public AActor
{
    GENERATED_BODY()

public:
    ASpeedPadActor();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // Overlap
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
    // メッシュ
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* Mesh;

    UPROPERTY(VisibleAnywhere)
    USceneComponent* DirectionRoot;

    // 加速方向アロー
    UPROPERTY(VisibleAnywhere)
    class UArrowComponent* DirectionArrow;

    // プレイヤー参照
    UPROPERTY()
    class ACharacter* OverlappingPlayer = nullptr;

    // 加速量
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AcceleratePower = 2000.f;

    // 勝手に進む床速度
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BaseSpeed = 600.f;
};
