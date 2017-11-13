// Fill out your copyright notice in the Description page of Project Settings.

 
#include "TankBarrel.h"
#include "Engine/World.h"

void UTankBarrel::Elevate(float DegreesPerSecond)
{

	//Move the Barrel the right amount per frame
	DegreesPerSecond = FMath::Clamp<float>(DegreesPerSecond, -1, +1);
	auto ElevationChange = DegreesPerSecond * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
	
	SetRelativeRotation(FRotator(RawNewElevation, 0, 0));
}



