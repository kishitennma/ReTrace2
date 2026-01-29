#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MonsterEffectManager.h"
#include "Sound/SoundBase.h"
#include "MovingMonster.generated.h"

// ===== Forward Declarations =====
class UBoxComponent;
class UMovingMonsterAnimInstance;

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
    // ====================
    // 通常制御
    // ====================

    /** アクティブ化（Triggerから呼ぶ） */
    UFUNCTION(BlueprintCallable)
    void ActivateMonster();

    /** プレイヤーがゴールしたら呼ばれる */
    UFUNCTION(BlueprintCallable)
    void OnGoalReached();

    // ====================
    // クリア演出（AnimNotify から）
    // ====================

    /** 咆哮終了 */
    UFUNCTION()
    void OnRoarFinished();

    /** TakeOff 終了 */
    UFUNCTION()
    void OnTakeOffFinished();

    // ====================
    // 既存：死亡演出
    // ====================

    UPROPERTY(EditAnywhere, Category = "Animation")
    UAnimMontage* DeathMontage;

    void PlayDeath();

    // ====================
    // 状態
    // ====================

    /** 移動中フラグ */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster")
    bool bIsActive = false;

    UPROPERTY(BlueprintReadWrite, Category = "State")
    bool bIsDead = false;

    // ====================
    // Collision
    // ====================

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
    UBoxComponent* HitCollision;

protected:
    // ====================
    // Collision Events
    // ====================

    UFUNCTION()
    void OnMonsterHit(
        UPrimitiveComponent* HitComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        FVector NormalImpulse,
        const FHitResult& Hit
    );

    UFUNCTION()
    void OnOverlapBegin(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );

    // ====================
    // Sound
    // ====================

    /** GeometryCollection ヒット音 */
    UPROPERTY(EditAnywhere, Category = "Sound")
    USoundBase* HitSound;

    /** 多重再生防止 */
    bool bCanPlayHitSound = true;

    UPROPERTY(EditAnywhere, Category = "Sound")
    float HitSoundCooldown = 0.3f;

    FTimerHandle HitSoundTimer;

    // ====================
    // Effect / Anim
    // ====================

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
    AMonsterEffectManager* EffectManager;

    /** AnimInstance キャッシュ */
    UPROPERTY()
    UMovingMonsterAnimInstance* MonsterAnim;

    // ====================
    // Movement
    // ====================

    /** BP で編集できる速度 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster")
    float MoveSpeed = 300.0f;
};
