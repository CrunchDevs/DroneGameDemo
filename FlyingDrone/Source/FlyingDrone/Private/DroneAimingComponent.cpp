// Fill out your copyright notice in the Description page of Project Settings.

#include "DroneAimingComponent.h"
#include "Projectile.h"
#include "Drone.h"

// Sets default values for this component's properties
UDroneAimingComponent::UDroneAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDroneAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDroneAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDroneAimingComponent::Initialize(ADrone* NewDrone)
{
	this->Drone = NewDrone;
}

void UDroneAimingComponent::Fire()
{
	if (ProjectileBlueprint && Drone)
	{
		FVector RightSocketLocation = Drone->GetRootComponent()->GetSocketLocation(FName("RightWeapon"));
		FVector LeftSocketLocation = Drone->GetRootComponent()->GetSocketLocation(FName("LeftWeapon"));

		FRotator RightSocketRotation = Drone->GetRootComponent()->GetSocketRotation(FName("RightWeapon"));
		FRotator LeftSocketRotation = Drone->GetRootComponent()->GetSocketRotation(FName("LeftWeapon"));

		AProjectile* RightProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, RightSocketLocation, RightSocketRotation);
		AProjectile* LeftProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, LeftSocketLocation, LeftSocketRotation);
		RightProjectile->LaunchProjectile(LaunchSpeed);
		LeftProjectile->LaunchProjectile(LaunchSpeed);
	}
}

