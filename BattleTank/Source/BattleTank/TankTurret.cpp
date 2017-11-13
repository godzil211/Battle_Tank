// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"

void UTankTurret::Rotate(float DegreesPerSecond)
{

	//Move the Turret the right amount per frame
	DegreesPerSecond = FMath::Clamp<float>(DegreesPerSecond, -1, +1);
	auto RotationChange = DegreesPerSecond * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Rotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0, Rotation, 0));
}

