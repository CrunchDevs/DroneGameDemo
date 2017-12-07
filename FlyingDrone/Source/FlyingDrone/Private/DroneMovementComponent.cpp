// Fill out your copyright notice in the Description page of Project Settings.

#include "DroneMovementComponent.h"
#include "Drone.h"
#include "Engine/World.h"



UDroneMovementComponent::UDroneMovementComponent()
{
	Acceleration = 25.f;
	MaxSpeed = 10000.f;
	MinSpeed = 0.f;
	TurnSpeed = 75.f;
	CurrentForwardSpeed = 0.f;
}

void UDroneMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	const FVector LocalMove = FVector(CurrentForwardSpeed * DeltaTime, 0.f, 0.f);

	auto Drone = Cast<ADrone>(GetPawnOwner());
	Drone->AddActorLocalOffset(LocalMove, true);

	FVector DeltaRotation(0, 0, 0);
	FQuat QuatRotation;
	if(!bIsTurning)
	{
		//CurrentRollSpeed = FMath::FInterpTo(CurrentRollSpeed, -GetOwner()->GetActorRotation().Roll, GetWorld()->GetDeltaSeconds(), 2.f);
		//UE_LOG(LogTemp, Log, TEXT("Roll: %f"), CurrentRollSpeed)
	}
	DeltaRotation.Y = CurrentPitchSpeed * DeltaTime;
	DeltaRotation.Z = CurrentYawSpeed * DeltaTime;
	DeltaRotation.X = CurrentRollSpeed * DeltaTime;

	// Rotate plane
	Drone->AddActorLocalRotation(FQuat::MakeFromEuler(DeltaRotation));

	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
		return;


	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UDroneMovementComponent::MoveForward(float Val)
{
	CurrentForwardSpeed = FMath::Clamp(Val, MinSpeed, MaxSpeed);
}

void UDroneMovementComponent::MoveUp(float Val)
{
	// Target pitch speed is based in input
	float TargetPitchSpeed = (Val * TurnSpeed * -1.f);

	// When steering, we decrease pitch slightly
	TargetPitchSpeed += (FMath::Abs(CurrentYawSpeed) * -0.2f);

	// Smoothly interpolate to target pitch speed
	CurrentPitchSpeed = FMath::FInterpTo(CurrentPitchSpeed, TargetPitchSpeed, GetWorld()->GetDeltaSeconds(), 2.f);
}

void UDroneMovementComponent::MoveRight(float Val)
{
	// Target yaw speed is based on input
	float TargetYawSpeed = (Val * TurnSpeed);

	// Smoothly interpolate to target yaw speed
	CurrentYawSpeed = FMath::FInterpTo(CurrentYawSpeed, TargetYawSpeed, GetWorld()->GetDeltaSeconds(), 2.f);

	// Is there any left/right input?
	const bool bIsTurning = FMath::Abs(Val) > 0.2f;

	// If turning, yaw value is used to influence roll
	// If not turning, roll to reverse current roll value.
	//float TargetRollSpeed = bIsTurning ? (CurrentYawSpeed * 0.5f) : (-GetOwner()->GetActorRotation().Roll);
	float TargetRollSpeed = CurrentYawSpeed * 0.5f;
	// Smoothly interpolate roll speed
	CurrentRollSpeed = FMath::FInterpTo(CurrentRollSpeed, TargetRollSpeed, GetWorld()->GetDeltaSeconds(), 2.f);
}

