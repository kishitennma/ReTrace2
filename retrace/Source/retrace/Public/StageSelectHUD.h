#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "StageSelectHUD.generated.h"

UCLASS()
class RETRACE_API AStageSelectHUD : public AHUD
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;
};
