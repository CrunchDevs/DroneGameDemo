// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DroneAimingComponent.generated.h"


class AProjectile;


UCLASS( ClassGroup=(Drone), meta=(BlueprintSpawnableComponent) )
class FLYINGDRONE_API UDroneAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDroneAimingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Called when Drone is firing 
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire(TSubclassOf<AProjectile> ProjectileBlueprint);
		
private:
	// Initialize in Blueprint Class
	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed;

	// Initialize in Blueprint Class
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TArray<TSubclassOf<AProjectile>> Projectiles;
	


	
};
