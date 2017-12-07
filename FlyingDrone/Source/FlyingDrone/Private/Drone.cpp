// Fill out your copyright notice in the Description page of Project Settings.

#include "Drone.h"

// Sets default values
ADrone::ADrone()
{
	PrimaryActorTick.bCanEverTick = true;
	DroneMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("DroneMesh"));
	SetRootComponent(DroneMesh);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(FName("DroneSpringArm"));
	SpringArm->AttachToComponent(DroneMesh, FAttachmentTransformRules::KeepRelativeTransform);
	
	DroneCamera = CreateDefaultSubobject<UCameraComponent>(FName("DroneCamera"));
	DroneCamera->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform);
}

float ADrone::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0)
	{
		OnDeath.Broadcast();
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Cyan, TEXT("Dead"));
	}	
	
	return DamageToApply;
}

float ADrone::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}

// Called when the game starts or when spawned
void ADrone::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartingHealth;
}

void ADrone::Tick(float DeltaTime)
{
	SetCameraRotation();
}

void ADrone::NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	CurrentHealth -= 5;
	UE_LOG(LogTemp, Warning, TEXT("Health: %d"), CurrentHealth)
	if (CurrentHealth <= 0)
		OnDeath.Broadcast();

	// Deflect along the surface when we collide.
	FRotator CurrentRotation = GetActorRotation();
	SetActorRotation(FQuat::Slerp(CurrentRotation.Quaternion(), HitNormal.ToOrientationQuat(), 0.025f));
}

void ADrone::SetCameraRotation()
{

	//Controller->GetControlRotation();
}

