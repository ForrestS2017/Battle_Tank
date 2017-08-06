// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:  

	virtual void BeginPlay() override;

#if ENABLE_VISUAL_LOG
	virtual void Tick(float DeltaSeconds) override;
#endif


	//How close can the AI tank get
	UPROPERTY(EditAnywhere, Category = Setup) // Consider EditDefaultsOnly
	float AcceptanceRadius = 300;

	virtual void SetPawn(APawn* InPawn) override;

};
