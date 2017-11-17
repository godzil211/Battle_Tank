// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */

class ATank;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()


// any variable exposed to blueprint must be in protected because a blueprint created 
// from a c++ class is child of that class
protected:

	// How close can the AI tank get to the player
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 3000; // in cms

public:


	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
	 
};
