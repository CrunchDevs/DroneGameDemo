// Fill out your copyright notice in the Description page of Project Settings.

#include "DronePlayerController.h"
#include "Drone.h"
#include "Components/StaticMeshComponent.h"

void ADronePlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		ADrone* PossessedDrone = Cast<ADrone>(InPawn);
		if (!ensure(PossessedDrone)) return; 
		PossessedDrone->OnDeath.AddUniqueDynamic(this, &ADronePlayerController::OnPossedDroneDeath);
		//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Cyan, PossessedDrone->GetName());
	}
}

void ADronePlayerController::OnPossedDroneDeath()
{
	//auto qw = GetPawn()->GetRootComponent()->IsSimulatingPhysics();
	APawn * Drone = GetPawn();
	if (Drone)
		if (Drone->GetRootComponent()->IsSimulatingPhysics())
			true;
			//Drone->GetComponentByClass<UStaticMeshComponent>()
// 	auto qwe = Cast<UStaticMeshComponent>();
// 	if(qwe)
// 		qwe->SetSimulatePhysics(true);
	StartSpectatingOnly();
}

