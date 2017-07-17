// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max downward speed, +1 is max up movement
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category= Setup)
		float MaxDegreesperSecond = 20.0f;	//Sensible Default
	UPROPERTY(EditAnywhere, Category = Setup)
		float MinElevationDegrees = 0.0f;	//Sensible Default
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxElevationDegrees = 40.0f;	//Sensible Default


	
};