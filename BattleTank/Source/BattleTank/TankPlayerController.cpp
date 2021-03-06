// Fill out your copyright notice in the Description page of Project Settings.

 
#include "TankPlayerController.h"
#include  "TankAimingComponent.h"
#include "Engine/World.h"
#include "Tank.h"

void ATankPlayerController::SetPawn(APawn* InPawn)
{

	Super::SetPawn(InPawn);
	if (InPawn)
	{

		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		//Subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
	}

}
 
void ATankPlayerController::OnPossessedTankDeath() {

	StartSpectatingOnly();
}


void ATankPlayerController::BeginPlay()
{

	Super::BeginPlay();

	//auto ControlledTank = GetControlledTank();

	//	if (!ControlledTank)
	//	{
	//		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank"));
	//	}
	//	else
	//	{

	//		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing %s"), *(ControlledTank->GetName()) );

	//	}


		auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
		if (ensure(AimingComponent))
		{
			FoundAimingComponent(AimingComponent);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Player Controller can't find aiming component at begin play"));
		}
}


// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}



void ATankPlayerController::AimTowardsCrosshair()
{
	 
	if (!GetPawn()) { return; } // e.g. when not possesing.
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
	//	UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString());

		AimingComponent->AimAt(HitLocation);
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
		return GetLookVectorHitLocation(LookDirection, HitLocation);

	//	UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *LookDirection.ToString());
	}

	 

	return false;
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
		ECollisionChannel::ECC_Camera)
	
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