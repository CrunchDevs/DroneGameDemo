// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DronePlayerController.generated.h"




/**
 * 
 */
UCLASS()
class FLYINGDRONE_API ADronePlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
private:
	void SetPawn(APawn* InPawn);

	UFUNCTION()
	void OnPossedDroneDeath();
};
