// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "GameFramework/Pawn.h"
#include "Drone.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDroneDelegate);

UCLASS()
class FLYINGDRONE_API ADrone : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADrone();

	// Called by the engine when actor damage is dealt
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	// Return current health as a percentage of starting health, between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup")
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
	int32 CurrentHealth; // Initialised in Begin Play

	FDroneDelegate OnDeath;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent * DroneMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USpringArmComponent * SpringArm;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UCameraComponent * DroneCamera;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
private:

	void SetCameraRotation();
	
};
