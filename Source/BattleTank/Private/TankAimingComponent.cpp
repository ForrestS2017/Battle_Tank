// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{

	if (!Barrel) return;
	//UE_LOG(LogTemp, Warning, TEXT("%s aiming at : Hit Location: %s from %s"), *OurTankName, *HitLocation.ToString(), *BarrelLocation.ToString());
	FVector OutLaunchVelocity;	//Out parameter of a vector with launch speed & direction
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed,
		false, 0.0f, 0.0f, ESuggestProjVelocityTraceOption::DoNotTrace);

	if (bHaveAimSolution)	//Calculate OutLaunchVelocity
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto Time = GetWorld()->GetTimeSeconds();
		//Move barrel frame-specific amount (GIVEN MAX ELEVATION SPEED)
		UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found"), Time);
		MoveBarrel(AimDirection);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Aim Solve. Velocity insufficient"));
	}
	//If no solution, do nothing
	
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	//Work out rDifference between current and required rotation
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimAtRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAtRotator - BarrelRotator;

	//Move barrel frame-specific amount (GIVEN MAX ELEVATION SPEED)
	Barrel->Elevate(5.0);	//TODO remove magic number

}