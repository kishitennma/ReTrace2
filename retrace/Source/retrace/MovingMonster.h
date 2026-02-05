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
   UFUNCTION()
    void StartFlyForward();
    /** Roar Montage 完了 */
    UFUNCTION()
    void OnRoarMontageEnded(UAnimMontage* Montage, bool bInterrupted);

    /** TakeOff Montage 完了 */
    UFUNCTION()
    void OnTakeOffMontageEnded(UAnimMontage* Montage, bool bInterrupted);

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
    //咆哮
    UPROPERTY(EditAnywhere, Category = "Sound")
    USoundBase* RoarSound;
    UPROPERTY(EditAnywhere, Category = "Sound")
    USoundBase* MonsterStep;

    UPROPERTY(EditAnywhere, Category = "Sound")
    USoundBase* MonsterWing;

    bool wallbreak = false;

    bool bCanPlayRoarSound = true;
   
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

    UPROPERTY(VisibleAnywhere)
    USceneComponent* MeshRoot;


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
    FTimerHandle ClearWidgetTimerHandle;
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


    FVector InitialForward;       // TakeOff前の進行方向を保持
    FRotator InitialMeshRotation; // メッシュの初期回転
    bool bRotatingForTakeOff = false;
    float TakeOffRotateElapsed = 0.f;
    float TakeOffRotateDuration = 1.f;
    FRotator TakeOffStartMeshRotation;
    FRotator TakeOffTargetMeshRotation;

    /** BPで編集可能な移動速度 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster")
    float MoveSpeed = 300.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster|Fly")
    float FlySpeed = 600.f;
};
