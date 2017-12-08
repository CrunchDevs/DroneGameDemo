// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "DronePlayerController.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create projectile movement component
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement Component"));
	ProjectileMovement->bAutoActivate = false;
	ProjectileMovement->ProjectileGravityScale = 0.f;

	// Generate collision mesh to determinate hit
	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	// Bind OnHit to Component
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{	
	TSubclassOf<UDamageType> DamageType;
	UGameplayStatics::ApplyDamage(OtherActor, WeaponInfo.Damage, GetWorld()->GetFirstPlayerController(), this, DamageType);

	CollisionMesh->DestroyComponent();
	FTimerHandle Timer;
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &AProjectile::OnTimerExpire, WeaponInfo.DestroyDelay, false);
}



void AProjectile::LaunchProjectile(float LaunchSpeed)
{
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * LaunchSpeed);
	ProjectileMovement->Activate();
}

void AProjectile::InitializeDroneWeaponInfo(int32 Damage, float DestroyDelay, bool bWaterProof)
{
	WeaponInfo.Damage = Damage;
	WeaponInfo.DestroyDelay = DestroyDelay;
	WeaponInfo.bIsWaterProof = bWaterProof;
}

void AProjectile::OnTimerExpire()
{
	Destroy();
}