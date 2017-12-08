// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Structures/DroneInfo.h"
#include "Drone.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDroneDelegate);
DECLARE_EVENT(ADrone, FOnHitWaterEvent)

class UStaticMeshComponent;
class UDroneAimingComponent;
class UDroneMovementComponent;

UCLASS()
class FLYINGDRONE_API ADrone : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADrone();

	// Return current health as a percentage of starting health, between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

	// Delegate that called when Drone is dead
	FDroneDelegate OnDeath;

	// Called when Drone under the water
	FOnHitWaterEvent HitWater;

protected:
	///Begin function override
	// Called by the engine when actor damage is dealt
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	///End function override

public:
	UFUNCTION(BlueprintCallable, Category = "Drone|Setup")
	void InitializeDroneInfo(int32 Health, int32 CritChance);

// 	UFUNCTION(BlueprintCallable, Category = "Drone|Info")
// 	FDroneInfo GetDroneInfo() const
// 	{
// 		return DroneInfo;
// 	}
// 
// 	UFUNCTION(BlueprintCallable, Category = "Drone|Info")
// 	FDroneStateInfo GetDroneStateInfo() const
// 	{
// 		return DroneState;
// 	}
	UPROPERTY()
	FDroneInfo DroneInfo;
	UPROPERTY()
	FDroneStateInfo DroneState;

private:


	
};
