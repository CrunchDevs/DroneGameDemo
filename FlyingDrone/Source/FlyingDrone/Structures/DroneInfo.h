#pragma once

#include "CoreMinimal.h"
#include "DroneInfo.generated.h"

USTRUCT(BlueprintType)
struct FDroneInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	int32 CurrentHealth;
	UPROPERTY()
	int32 MaxHealth;
	UPROPERTY()
	int32 CritChance;
};


USTRUCT(BlueprintType)
struct FDroneStateInfo
{
	GENERATED_USTRUCT_BODY()


	UPROPERTY()
	bool bIsInWater;
	UPROPERTY()
	bool bIsDead;
};


USTRUCT(BlueprintType)
struct FDroneWeapon
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY()
	float Damage;
	UPROPERTY()
	float DestroyDelay;
	UPROPERTY()
	bool bIsWaterProof;
};


USTRUCT(BlueprintType)
struct FDroneShield
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite)
	float AbsorptionAmount;
	UPROPERTY(BlueprintReadWrite)
	bool bIsWaterProof;
};