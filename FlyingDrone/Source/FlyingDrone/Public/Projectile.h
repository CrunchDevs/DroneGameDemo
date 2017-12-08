// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Structures/DroneInfo.h"
#include "Projectile.generated.h"


UCLASS()
class FLYINGDRONE_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:	
	void LaunchProjectile(float LaunchSpeed);

	UFUNCTION(BlueprintCallable, Category = "Drone|Weapon")
	void InitializeDroneWeaponInfo(int32 Damage, float DestroyDelay, bool bWaterProof);

	UPROPERTY()
	FDroneWeapon WeaponInfo;
private:

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void OnTimerExpire();

	UProjectileMovementComponent* ProjectileMovement = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* CollisionMesh = nullptr;

};
