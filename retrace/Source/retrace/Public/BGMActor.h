// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BGMActor.generated.h"

class AMovingMonster;

UCLASS()
class RETRACE_API ABGMActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABGMActor();
	UPROPERTY()
	UAudioComponent* BGMComponent;

	UPROPERTY(EditAnywhere, Category = "BGM")
	USoundBase* BGM;

	UFUNCTION()
	void CheckAndPlayMonsterBGM();

	void BGMstop();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
