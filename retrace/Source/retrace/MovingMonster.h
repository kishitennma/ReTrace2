#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MonsterEffectManager.h"
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

    UFUNCTION(BlueprintCallable)//プレイヤーがゴールしたら
    void OnGoalReached();

    UFUNCTION()
    void OnOverlapBegin(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );
  
    UPROPERTY(EditAnywhere, Category = "Animation")
    UAnimMontage* DeathMontage;

    void PlayDeath();
   // void OnDeathAnimationFinished();

    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
    AMonsterEffectManager* EffectManager;

    // BP で編集できる速度
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster")
    float MoveSpeed = 300.0f;

    // 移動中フラグ
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster")
    bool bIsActive = false;
    UPROPERTY(BlueprintReadWrite, Category = "State")
    bool bIsDead = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
    class UBoxComponent* HitCollision;

   

};
