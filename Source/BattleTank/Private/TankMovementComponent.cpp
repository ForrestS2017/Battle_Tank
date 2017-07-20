// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialize(UTankTrack* TrackToSet_L, UTankTrack* TrackToSet_R)
{

	if (!TrackToSet_L || !TrackToSet_R) { return; }
	
	Track_L = TrackToSet_L;
	Track_R = TrackToSet_R;

}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	//No need to call Super as we're replacing the functionality of the original
	
	//We get safe normals so when we find the dotproduct, we dont get anything greater than 1
	auto TankForwardDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	//Now, our dot product
	auto ForwardThrow = FVector::DotProduct(TankForwardDirection, AIForwardIntention);
	IntendMoveForward(ForwardThrow);
	//UE_LOG(LogTemp, Warning, TEXT("%s vectoring to %s"), *TankName, *MoveVelocityString)
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	Track_L->SetThrottle(Throw);
	Track_R->SetThrottle(Throw);

}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	Track_L->SetThrottle(Throw);
	Track_R->SetThrottle(-Throw);
}


