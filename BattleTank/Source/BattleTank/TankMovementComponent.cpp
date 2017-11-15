// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"



void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {


	if (!LeftTrackToSet || !RightTrackToSet) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}


void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	//No need to call Super as we're replacing the functionality here
//	auto TankName = GetOwner()->GetName();
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal(); // Returns the local X axis of the tank
	auto AIForwardIntention = MoveVelocity.GetSafeNormal(); // GetSafe normaliza el vector ( lo divide por la longitud) para crear unit vectors de -1 a +1.
	
	// El tanque enemigo se moverá a tu dirección
	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	//IntendMoveForward(ForwardThrow);

	// El tanque enemigo enfocará a tu dirección ( importa el orden los parametros hay que probar cual funciona)
	auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	IntendTurnRight(RightThrow);
	UE_LOG(LogTemp, Warning, TEXT("Right: %f , Forward: %f"), RightThrow, ForwardThrow);
}


void UTankMovementComponent::IntendMoveForward(float Throw)
{
	
	if (!LeftTrack || !RightTrack) { return; }
		LeftTrack->SetThrottle(Throw);
		RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{

	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}
