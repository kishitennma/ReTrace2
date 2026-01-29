#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AudioManager.generated.h"

UCLASS()
class RETRACE_API AAudioManager : public AActor
{
    GENERATED_BODY()

public:
    AAudioManager();

    UPROPERTY(EditAnywhere, Category = "BGM")
    USoundBase* TitleBGM;

    UPROPERTY(EditAnywhere, Category = "BGM")
    USoundBase* StageBGM;

    UPROPERTY(EditAnywhere, Category = "BGM")
    USoundBase* DangerBGM;

    void PlayBGM(USoundBase* NewBGM);

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    UAudioComponent* BGMComponent;
};
