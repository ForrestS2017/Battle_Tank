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

void UTankAimingComponent::BeginPlay()
{
	//So first fire is after reload
	LastFireTime = FPlatformTime::Seconds();
	Super::BeginPlay();

	
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if (RoundsLeft <= 0)
	{
		FiringState = EFiringState::OutofAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}

}

void UTankAimingComponent::AimAt(FVector HitLocation)
{

	if (!ensure(Barrel)) return;
	FVector OutLaunchVelocity;	//Out parameter of a vector with launch speed & direction
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed,
		false, 0.0f, 0.0f, ESuggestProjVelocityTraceOption::DoNotTrace);

	if (bHaveAimSolution)	//Calculate OutLaunchVelocity
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
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
	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate( DeltaRotator.Yaw );

}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	auto BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.03);
}



void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel)) return;
	if (!ensure(ProjectileBlueprint)) return;

	if (FiringState == EFiringState::Locked || FiringState == EFiringState::Aiming)
	{
		//Spawn projectile at tip of barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		FiringState = EFiringState::Reloading;
		RoundsLeft--;
	}
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

int32 UTankAimingComponent::GetRoundsLeft() const
{
	return RoundsLeft;
}