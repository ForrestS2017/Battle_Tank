// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Error, TEXT("NO CONTROLLED TANK"));
	}
	/*else {
		UE_LOG(LogTemp, Warning, TEXT("AIController BeginPlay: %s"), *ControlledTank->GetName());
	}*/

	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank) {
		UE_LOG(LogTemp, Error, TEXT("NO Player TANK"));
	}
	/*else {
		UE_LOG(LogTemp, Warning, TEXT("AI: PlayerTank is: %s"), *PlayerTank->GetName());
	}*/
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetPlayerTank()) {
		//TODO Move towards the player
		// Aim towards the player
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
		// Fire if ready
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}
