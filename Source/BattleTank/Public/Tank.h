// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankTrack;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

		ATank();

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		int32 StartingHealth = 100;
	
	UPROPERTY(VisibleAnywhere, Category = Health)
		int32 CurrentHealth = StartingHealth;

	virtual void BeginPlay() override;

public:
	// Called by engine when actor is damaged
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	// returns current health as a percentage of starting health ( 0 to 1 )
	UFUNCTION(BlueprintPure, Category = Health)
	float GetHealthPercent() const;

	FTankDelegate OnDeath;
};
