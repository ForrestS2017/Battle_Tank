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


