// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "DroneMovementComponent.generated.h"


/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FLYINGDRONE_API UDroneMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()
	
public:

	UDroneMovementComponent();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	void MoveForward(float Val);

	UFUNCTION(BlueprintCallable)
	void MoveUp(float Val);

	UFUNCTION(BlueprintCallable)
	void MoveRight(float Val);

public:
	//Accessors
	UFUNCTION(BlueprintPure)
	float GetMaximumSpeed()
	{
		return MaxSpeed;
	}

	UFUNCTION(BlueprintPure)
	float GetMinimumSpeed()
	{
		return MinSpeed;
	}

	UFUNCTION(BlueprintPure)
	float GetCurrentForwardSpeed()
	{
		return CurrentForwardSpeed;
	}

	UFUNCTION(BlueprintCallable)
	void SetCurrentForwardSpeed(float InCurrentForwardSpeed)
	{
		CurrentForwardSpeed = InCurrentForwardSpeed;
	}

	UFUNCTION(BlueprintPure)
	float GetAcceleration()
	{
		return Acceleration;
	}

private:

	//Properties
	/** How quickly forward speed changes */
	UPROPERTY(Category = Plane, EditAnywhere)
	float Acceleration;

	/** How quickly pawn can steer */
	UPROPERTY(Category = Plane, EditAnywhere)
	float TurnSpeed;

	/** Max forward speed */
	UPROPERTY(Category = Pitch, EditAnywhere)
	float MaxSpeed;

	/** Min forward speed */
	UPROPERTY(Category = Yaw, EditAnywhere)
	float MinSpeed;

	/** Current forward speed */
	float CurrentForwardSpeed;

	/** Current yaw speed */
	float CurrentYawSpeed;

	/** Current pitch speed */
	float CurrentPitchSpeed;

	/** Current roll speed */
	float CurrentRollSpeed;
};
