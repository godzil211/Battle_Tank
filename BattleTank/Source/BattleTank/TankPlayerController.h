// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

 
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * Responsible for helping the player aim.
 */

class ATank;
class UTankAimingComponent;
 
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);

private:
	
	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;


	// Start the tank moving the barrel so that a shot would hit 
	// where crosshair intersects the world
	void AimTowardsCrosshair();

	//Return an OUT paramaeter, true if hit landscape
	bool GetSightRayHitLocation(FVector& HitLocation) const;


	UPROPERTY(EditAnywhere)
		float CrosshairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
		float CrosshairYLocation = 0.3333;

	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000; // 10 kms in cms

		
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

};
