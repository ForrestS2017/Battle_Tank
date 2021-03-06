// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "TankAIController.h"

// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn); //necessary to run this function
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) return;

		// Subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);

	}


}

void ATankAIController::OnPossessedTankDeath()
{
	if (!ensure(GetPawn())) return;	// TODO remove ensure if OK
	GetPawn()->DetachFromControllerPendingDestroy();

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (ensure(PlayerTank && ControlledTank)) 
	{

		auto testing = MoveToActor(PlayerTank, AcceptanceRadius); //TODO check radius in cm

		auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();

		if (!ensure(AimingComponent)) { return; }

		AimingComponent->AimAt(PlayerTank->GetActorLocation());

		if (AimingComponent->GetFiringState() == EFiringState::Locked)
		{
			AimingComponent->Fire();
		}
	}
}


