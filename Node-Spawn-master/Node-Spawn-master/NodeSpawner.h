// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NodeSpawner_Parent.h"
#include "NodeSpawner.generated.h"

UCLASS()
class BLOCKS_API ANodeSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANodeSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Coordinates of x, y, z
	float x_coord;								
	float y_coord;
	float z_coord;

	float generateCoord(float DeltaTime);

	float currentTime;									// Keep the current alive time

	FTransform ourOldSpawnLocation;						// Holds all of our old spawn information
	FVector ourLoc;										// Hold our spawn location
	FRotator ourRotation;								// Hold the rotation of the object

	UPROPERTY(EditDefaultsOnly, Category = "Our Spawning Object")
		TSubclassOf<ANodeSpawner_Parent> ourSpawningObject;					// Holds the blueprints of the object we want to spawn

};
