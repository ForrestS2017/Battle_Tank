// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"	//Must be last include

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintCallable, Category = Setup)
		ATank* GetControlledTank() const;

private:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	// Have tank move barrel to aim towards crosshair intersection with world mesh
	void AimTowardsCrosshair();

	bool GetSightrayHitLocation(FVector& OUTHitLocation);	//true if hit landscape

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation);
	
	UPROPERTY(EditDefaultsOnly)
		float CrossHairLocationX = 0.5f;
	
	UPROPERTY(EditDefaultsOnly)
		float CrossHairLocationY = 0.333f;

	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000.0f;
};
