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

    // �ړ����x�iBlueprint�ҏW�j
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float MoveSpeed = 300.0f;

    // �N���t���O
    UPROPERTY(BlueprintReadWrite)
    bool bIsActive = false;

    // �N���p�֐��iBlueprint�ł��Ăׂ�j
    UFUNCTION(BlueprintCallable)
    void ActivateMonster();
};
