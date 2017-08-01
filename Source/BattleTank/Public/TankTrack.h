// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Used to set maximum driving force, to apply force to the Tank
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// Sets a throttle between -1 to +1
	UFUNCTION(BlueprintCallable, Category = Throttle)
		void SetThrottle(float Throttle);

	// Max Force per track in Newtons
	UPROPERTY(EditAnywhere, Category = Throttle)
		float TrackMaxDrivingForce = 400000;	// 40 ton tank, 1g acceleration
	
private:
	UTankTrack();

	void ApplySidewaysForce();

	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
