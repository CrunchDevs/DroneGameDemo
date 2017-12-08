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

void UDroneAimingComponent::Fire(TSubclassOf<AProjectile> ProjectileBlueprint)
{
	if (!ProjectileBlueprint) return;

	if (!Projectiles.Contains(ProjectileBlueprint)) return;

	ADrone* Drone = Cast<ADrone>(GetOwner());
	if (!Drone) return;
	if (Drone->DroneState.bIsInWater || Drone->DroneState.bIsDead) return;
	

	TArray<FName> Sockets = GetOwner()->GetRootComponent()->GetAllSocketNames();

	if (Sockets.Num() == 0) return;
	for (FName Socket : Sockets)
	{
		FVector SocketLocation = GetOwner()->GetRootComponent()->GetSocketLocation(Socket);
		FRotator SocketRotation = GetOwner()->GetRootComponent()->GetSocketRotation(Socket);

		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, SocketLocation, SocketRotation);

		if (!Projectile) return;
		Projectile->LaunchProjectile(LaunchSpeed);
	}	
}

