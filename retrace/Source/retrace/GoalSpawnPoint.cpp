// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalSpawnPoint.h"

// Sets default values
AGoalSpawnPoint::AGoalSpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGoalSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGoalSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

