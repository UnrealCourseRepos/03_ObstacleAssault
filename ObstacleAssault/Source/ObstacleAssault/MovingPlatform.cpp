// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 1. Move platform forwards
		// 1.1 Get current location
	FVector CurrentLocation = GetActorLocation();

		// 1.2 Add vector to that location
	CurrentLocation += PlatformVelocity * DeltaTime;
		// 1.3 Set the location
	SetActorLocation(CurrentLocation);

	// 2. Send platform back if gone too far
		// 2.1 Check how far we have moved
	const float DistanceMoved =  FVector::Dist(StartLocation, CurrentLocation);

	if (DistanceMoved > MoveDistance)
	{
		// 2.2 Reverse direction of motion if gone too far
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation += MoveDirection * MoveDistance;
		SetActorLocation(StartLocation);

		PlatformVelocity = -PlatformVelocity;
	}

}

