#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MovingMonster.generated.h"

UCLASS()
class RETRACE_API AMovingMonster : public ACharacter
{
    GENERATED_BODY()

public:
    AMovingMonster();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

public:
    // アクティブ化（Triggerから呼ぶ）
    UFUNCTION(BlueprintCallable)
    void ActivateMonster();

    UFUNCTION()
    void OnOverlapBegin(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );


    


    // BP で編集できる速度
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster")
    float MoveSpeed = 300.0f;

    // 移動中フラグ
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster")
    bool bIsActive = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
    class UBoxComponent* HitCollision;

   

};
