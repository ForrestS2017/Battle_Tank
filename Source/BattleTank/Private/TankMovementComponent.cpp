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
	/* Now, our dot product will yield the parallelness of the two vectors. parallel same direction = 1 = go forward */
	auto ForwardThrow = FVector::DotProduct(TankForwardDirection, AIForwardIntention);
	IntendMoveForward(ForwardThrow);
	/* Cross product will yield how perpendicular the vectors are. If they're perpendicular you yield 1 */
	auto RightThrow = FVector::CrossProduct(TankForwardDirection, AIForwardIntention).Z;
	IntendTurnRight(RightThrow);
	UE_LOG(LogTemp, Warning, TEXT("%s: Right: %f, Forward: %f"), *GetOwner()->GetName(), ForwardThrow, RightThrow);

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


