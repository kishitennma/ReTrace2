// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GoalSpawnPoint.generated.h"

UCLASS()
class RETRACE_API AGoalSpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGoalSpawnPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool HasActive;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
