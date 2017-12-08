// Fill out your copyright notice in the Description page of Project Settings.

#include "Drone.h"
#include "Components/StaticMeshComponent.h"
#include "DroneMovementComponent.h"
#include "DroneAimingComponent.h"


// Sets default values
ADrone::ADrone()
{
	PrimaryActorTick.bCanEverTick = false;
	
}

float ADrone::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, DroneInfo.CurrentHealth);

	DroneInfo.CurrentHealth -= DamageToApply;
	if (DroneInfo.CurrentHealth <= 0)
	{
		OnDeath.Broadcast();
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Cyan, TEXT("Dead"));
	}	
	
	return DamageToApply;
}

float ADrone::GetHealthPercent() const
{
	return (float)DroneInfo.CurrentHealth / (float)DroneInfo.MaxHealth;
}

// Called when the game starts or when spawned
void ADrone::BeginPlay()
{
	Super::BeginPlay();
	DroneInfo.CurrentHealth = DroneInfo.MaxHealth;

	DroneState.bIsDead = false;
	DroneState.bIsInWater = false;
}

void ADrone::NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	DroneInfo.CurrentHealth -= 5;
	//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Cyan, FString::Printf__VA(TEXT("%f"), GetHealthPercent()));
	if (DroneInfo.CurrentHealth <= 0)
	{
		OnDeath.Broadcast();
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Cyan, TEXT("Dead"));
	}
	// Deflect along the surface when we collide.

	FRotator CurrentRotation = GetActorRotation();
	SetActorRotation(FQuat::Slerp(CurrentRotation.Quaternion(), HitNormal.ToOrientationQuat(), 0.025f));
}

void ADrone::InitializeDroneInfo(int32 Health, int32 CritChance)
{
	DroneInfo.MaxHealth = Health;
	DroneInfo.CurrentHealth = Health;
	DroneInfo.CritChance = CritChance;

	DroneState.bIsDead = false;
	DroneState.bIsInWater = false;

}

