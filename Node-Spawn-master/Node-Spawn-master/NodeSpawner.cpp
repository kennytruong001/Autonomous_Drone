// Fill out your copyright notice in the Description page of Project Settings.


#include "NodeSpawner.h"
#include "GameFramework/Actor.h"
#include <cmath>
#include <time.h>
// Sets default values
ANodeSpawner::ANodeSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	currentTime = 0.f;
	x_coord = 0.f;
	y_coord = 0.f;
	z_coord = 0.f;
	ourRotation.ZeroRotator;
	ourLoc.X = 0.f;
	ourLoc.Y = 0.f;
	ourLoc.Z = 0.f;
	srand(unsigned int(time(NULL)));

}

// Called when the game starts or when spawned
void ANodeSpawner::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("SPAWNING"));		//Debug Message for spawning
}
 
// Called every frame
void ANodeSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	currentTime = currentTime + 1 * DeltaTime;

	FString ourString = FString::SanitizeFloat(currentTime);

	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Our current time: ") + ourString);

	if (currentTime >= 0.5f)
	{
		x_coord = float(rand() % 2000 + (-1000));
		//generateCoord(DeltaTime);
		y_coord = float(rand() % 2000 + (-1000));
		z_coord = float(rand() % 5000 + 500);

		ourLoc.X = x_coord;
		ourLoc.Y = y_coord;
		ourLoc.Z = z_coord;

		// Create Spawn params
		FActorSpawnParameters spawnParams;

		// Who did the spawn and we are say this controller did
		spawnParams.Owner = this;

		spawnParams.Instigator = GetInstigator();

		ANodeSpawner_Parent* ourNewObject = GetWorld()->SpawnActor<ANodeSpawner_Parent>(ourSpawningObject, ourLoc, ourRotation, spawnParams);

		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::White, TEXT("We spawned an object "));			// debug

		//currentTime back to 0
		currentTime = 0.f;
	}
}


// Generates a 3D coordinate
float ANodeSpawner::generateCoord(float DeltaTime)
{
	float passBack = 0.f;

	passBack = FMath::RandRange(-20, 20);

	passBack = passBack + DeltaTime;			//gives an offset based on DeltaTime

	return passBack;
}
