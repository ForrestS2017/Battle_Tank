// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}
void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{

	if (!ensure(Barrel)) return;
	//UE_LOG(LogTemp, Warning, TEXT("%s aiming at : Hit Location: %s from %s"), *OurTankName, *HitLocation.ToString(), *BarrelLocation.ToString());
	FVector OutLaunchVelocity;	//Out parameter of a vector with launch speed & direction
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed,
		false, 0.0f, 0.0f, ESuggestProjVelocityTraceOption::DoNotTrace);

	if (bHaveAimSolution)	//Calculate OutLaunchVelocity
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		//auto Time = GetWorld()->GetTimeSeconds();
		////Move barrel frame-specific amount (GIVEN MAX ELEVATION SPEED)
		//UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found"), Time);
		MoveBarrel(AimDirection);
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("No Aim Solve. Velocity insufficient"));
	}
	//If no solution, do nothing
	
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	if (!ensure(Barrel || Turret)) return;
	//Work out rDifference between current and required rotation
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimAtRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAtRotator - BarrelRotator;
	DeltaRotator = DeltaRotator.GetNormalized();

	//Move barrel frame-specific amount (GIVEN MAX ELEVATION SPEED)
	Barrel->Elevate(DeltaRotator.Pitch);	//TODO remove magic number
	Turret->Rotate(DeltaRotator.Yaw);

}

void UTankAimingComponent::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) >= ReloadTimeInSeconds;
	if (!ensure(Barrel && ProjectileBlueprint)) return;

	if (isReloaded)
	{
		//Spawn projectile at tip of barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}