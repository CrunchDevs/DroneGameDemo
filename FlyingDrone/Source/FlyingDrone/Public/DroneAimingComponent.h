// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DroneAimingComponent.generated.h"


class AProjectile;
class ADrone;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
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

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialize(ADrone* NewDrone);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();
		
private:
	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	ADrone* Drone;


	
};
