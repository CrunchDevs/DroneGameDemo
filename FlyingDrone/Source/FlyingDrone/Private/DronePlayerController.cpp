// Fill out your copyright notice in the Description page of Project Settings.

#include "DronePlayerController.h"
#include "Drone.h"
#include "Components/StaticMeshComponent.h"
#include "DroneMovementComponent.h"
#include "DroneAimingComponent.h"

void ADronePlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		ADrone* PossessedDrone = Cast<ADrone>(InPawn);
		if (!ensure(PossessedDrone)) return; 
		PossessedDrone->OnDeath.AddUniqueDynamic(this, &ADronePlayerController::OnPossedDroneDeath);
		//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Cyan, PossessedDrone->GetName());
		PossessedDrone->HitWater.AddUFunction(this, FName("OnHitWater"));
	}
}

void ADronePlayerController::OnPossedDroneDeath()
{
	ADrone* PossessedDrone = Cast<ADrone>(GetPawn());
	if (PossessedDrone)
	{
		UDroneMovementComponent* MovementComponent = Cast<UDroneMovementComponent>(PossessedDrone->GetComponentByClass(UDroneMovementComponent::StaticClass()));
		UDroneAimingComponent* AimingComponent = Cast<UDroneAimingComponent>(PossessedDrone->GetComponentByClass(UDroneAimingComponent::StaticClass()));
		UStaticMeshComponent* MeshComponent = Cast<UStaticMeshComponent>(PossessedDrone->GetComponentByClass(UStaticMeshComponent::StaticClass()));
		
		if (MovementComponent)
			MovementComponent->Deactivate();
		if (AimingComponent)
			AimingComponent->Deactivate();
		if (MeshComponent)
			MeshComponent->SetSimulatePhysics(true);
	}
	
	StartSpectatingOnly();
}

void ADronePlayerController::OnHitWater()
{
	ADrone* PossessedDrone = Cast<ADrone>(GetPawn());
	if (PossessedDrone)
	{
		PossessedDrone->DroneState.bIsInWater = true;
	}
}