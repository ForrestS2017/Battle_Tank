// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Error, TEXT("NO CONTROLLED TANK"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController BeginPlay: %s"), *ControlledTank->GetName());
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return;}
	FVector HitLocation; //Out Parameter
	if (GetSightrayHitLocation(HitLocation)) {	//Has "side-effect" of line tracing
		//Tell controlled tank to aim at this point
		GetControlledTank()->AimAt(HitLocation);
	}
	else 
	{ 
		UE_LOG(LogTemp, Warning, TEXT("No Hit Location") );
		return; 
	}
}

// Get world location of linetrace throuhg corsshair, true if hits landscape
bool ATankPlayerController::GetSightrayHitLocation(FVector& OUTHitLocation) 
{
	
	//Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairLocationX, ViewportSizeY * CrossHairLocationY);
	
	// "Deproject the screen position of the corsshair to a world direction
	FVector LookDirection;
	FVector HitLocation;
	GetLookDirection(ScreenLocation, LookDirection);
	if ( GetLookVectorHitLocation(LookDirection, OUTHitLocation) )
	{
		return true;
	}
	return false;
	// Line-trace along that LookDirection and see what we hit (up to max range)
	
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation)
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto Endlocation = StartLocation + LookDirection*LineTraceRange;

	if (	GetWorld()->LineTraceSingleByChannel(
			HitResult, StartLocation, Endlocation,
			ECollisionChannel::ECC_Visibility)
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}
	return false;
}