// Fill out your copyright notice in the Description page of Project Settings.


#include "NodeSpawner_Parent.h"

// Sets default values
ANodeSpawner_Parent::ANodeSpawner_Parent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANodeSpawner_Parent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANodeSpawner_Parent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

