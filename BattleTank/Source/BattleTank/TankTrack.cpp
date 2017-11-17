// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"




	UTankTrack::UTankTrack()
	{
		PrimaryComponentTick.bCanEverTick = false;
	}


	void UTankTrack::BeginPlay()
	{
		OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);

	}

	void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
	{
	//	UE_LOG(LogTemp, Warning, TEXT(" I'm hit , I'm hit!"))

	 
		DriveTrack();
		//Apply sideways forces
		ApplySideWayForces();
		// reset Throtlle
		CurrentThrottle = 0;
	}


	

	void UTankTrack::ApplySideWayForces()
	{
		// Calculate the slippage speed
		auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
		// Work-out the required acceleration
		auto DeltaTime = GetWorld()->GetDeltaSeconds();
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


	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::DriveTrack()
{
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

