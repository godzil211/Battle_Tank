// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankPlayerController.h"
#include "Engine/World.h"


 



void ATankPlayerController::BeginPlay()
{

	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();

		if (!ControlledTank)
		{
			UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank"));
		}
		else
		{

			UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing %s"), *(ControlledTank->GetName()) );

		}
}


// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}



ATank* ATankPlayerController::GetControlledTank() const 

{

	return Cast<ATank>(GetPawn());


}

void ATankPlayerController::AimTowardsCrosshair()
{

	if (!GetControlledTank()) { return; }

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
	//	UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString());

		GetControlledTank()->AimAt(HitLocation);
		//Get word location of linetrace through crosshair 
		// If it hits the landscape 
			//Tell controlled tank to aim at this point
	}

}

bool  ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	 // Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	// De-project the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line-trace along that look direction and see what we hit ( up to max range)
		GetLookVectorHitLocation(LookDirection, HitLocation);

	//	UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *LookDirection.ToString());
	}

	 

	return true;
}


bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + LookDirection * LineTraceRange;

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility)
	
	)
	{
		// Set hit location
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false; // line trace didn't succeed
}



bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection);

}