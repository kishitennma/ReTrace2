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
    // クリア演出（AnimNotify から呼ばれる）
    // ====================

    /** 咆哮終了通知 */
    UFUNCTION()
    void OnRoarFinished();

    /** TakeOff終了通知 */
    UFUNCTION()
    void OnTakeOffFinished();

  
  
    // ====================
    // 状態
    // ====================

    /** 移動中フラグ */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster")
    bool bIsActive = false;

    /** 死亡済みフラグ */
    UPROPERTY(BlueprintReadWrite, Category = "State")
    bool bIsDead = false;

    /** 飛行中フラグ（StateMachine切り替え用） */
    UPROPERTY(BlueprintReadWrite, Category = "State")
    bool bIsFlying = false;

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

    /** ヒット音の多重再生防止フラグ */
    bool bCanPlayHitSound = true;
    UPROPERTY(BlueprintReadWrite, Category = "Monster|State")
    bool bHasStartedRoar = false;

    // TakeOff の再生フラグ
    UPROPERTY(BlueprintReadWrite, Category = "Monster|State")
    bool bHasStartedTakeOff = false;

    /** ヒット音再生間隔 */
    UPROPERTY(EditAnywhere, Category = "Sound")
    float HitSoundCooldown = 0.3f;

    FTimerHandle HitSoundTimer;

    // ====================
    // Effect / Anim
    // ====================

    /** エフェクトマネージャ参照 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
    AMonsterEffectManager* EffectManager;

    /** AnimInstance キャッシュ */
    UPROPERTY()
    UMovingMonsterAnimInstance* MonsterAnim;

    // ====================
    // Movement
    // ====================

    /** BPで編集可能な移動速度 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster")
    float MoveSpeed = 300.0f;
};
