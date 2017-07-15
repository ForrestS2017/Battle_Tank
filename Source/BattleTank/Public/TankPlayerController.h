// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"	//Must be last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:

	ATank* GetControlledTank() const;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	// Have tank move barrel to aim towards crosshair intersection with world mesh
	void AimTowardsCrosshair();

	bool GetSightrayHitLocation(FVector& OUTHitLocation);	//true if hit landscape

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation);
	
	UPROPERTY(EditAnywhere)
		float CrossHairLocationX = 0.5f;
	
	UPROPERTY(EditAnywhere)
		float CrossHairLocationY = 0.333f;

	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000.0f;
};
