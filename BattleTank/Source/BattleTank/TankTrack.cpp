// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"




	UTankTrack::UTankTrack()
	{
		PrimaryComponentTick.bCanEverTick = true;
	}

	void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
	{
		// Calculate the slippage speed
		auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
		// Work-out the required acceleration
		auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
		// Calculate and apply sideways (F = m a )
		auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent()); // we need to take the mass of the tank not the mass of the track
		auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // Two Tracks
		TankRoot->AddForce(CorrectionForce);
	}

void UTankTrack::SetThrottle(float Throttle) {

	//	auto Time = GetWorld()->GetTimeSeconds;
	//	auto Name = GetName();
	//	UE_LOG(LogTemp, Warning, TEXT("%s throttle : %f"), *Name , Throttle);


	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

