// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PawnMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * Responsible for driving the tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BluePrintCallable, Category = Setup)
		void Initialize(UTankTrack* TrackToSet_L, UTankTrack* TrackToSet_R);

	UFUNCTION(BluePrintCallable, Category = Input)
		void IntendMoveForward(float Throw);

	UFUNCTION(BluePrintCallable, Category = Input)
		void IntendTurnRight(float Throw);

	virtual void RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed) override;

private:

	UTankTrack* Track_L = nullptr;
	UTankTrack* Track_R = nullptr;
};
