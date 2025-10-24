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

public:
    virtual void Tick(float DeltaTime) override;

    // 移動速度（Blueprint編集可）
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float MoveSpeed = 300.0f;

    // 起動フラグ
    UPROPERTY(BlueprintReadWrite)
    bool bIsActive = false;

    // 起動用関数（Blueprintでも呼べる）
    UFUNCTION(BlueprintCallable)
    void ActivateMonster();
};
