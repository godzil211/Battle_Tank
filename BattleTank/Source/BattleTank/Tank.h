// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

 
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class UTankMovementComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()





public:

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable)
	void Fire();
	 
		
		

protected:
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent*  TankAimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* TankMovementComponent = nullptr;


private:
	// Sets default values for this pawn's properties
	ATank();


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	

	UPROPERTY(EditAnywhere, Category = "Firing")
		float LaunchSpeed = 4000.0; 

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	float ReloadTimeInSeconds = 30;


	//Local barrel reference for spawning projectile
	UTankBarrel* Barrel = nullptr;


	double LastFireTime = 0;
};
