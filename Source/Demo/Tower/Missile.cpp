// Fill out your copyright notice in the Description page of Project Settings.

#include "Missile.h"

#include "Sphere_component.h"
#include "Kismet/GameplayStatics.h"
#include "DemoCharacter.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AMissile::AMissile(const FObjectInitializer& ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Construct Collision Component
	CollisionComp = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("CollisionComp"));
	RootComponent = CollisionComp;

	// Construct Static Mesh Component
	MissileMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("MissileMesh"));
	MissileMesh->SetupAttachment(RootComponent);

	// Construct Projectile Movement Component
	ProjectileMovement = ObjectInitializer.CreateDefaultSubobject<UProjectileMovementComponent>(this, TEXT("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed =500.f;
	ProjectileMovement->MaxSpeed = 2500.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bInitialVelocityInLocalSpace = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->bIsHomingProjectile = false;
	ProjectileMovement->HomingAccelerationMagnitude = 0.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;
	ProjectileMovement->Velocity = FVector(0, 0, 0);

	// Bind our OnOverlapBegin Event
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AMissile::OnOverlapBegin);

	// Set Default Values for Variables
	hasTargetPosition = false;
	hasNoTarget = false;
	target = NULL;
	delayTimer = 0.f;
	hasFinishedDelay = false;
	lifetimeCountdown = 15.f;
	canBeDestroyed = false;
	PlayerInWorld = NULL;

	
}


void AMissile::BeginPlay()
{
	Super::BeginPlay();
	FindPlayer();

	// Before we find our target, launch the Missile upwards
	if (!hasTargetPosition)
	{
		ProjectileMovement->Velocity = GetActorUpVector() * 200.f;

		// BeginPlay with collision disabled so that the missile doesn't interact with other actors
		this->SetActorEnableCollision(false);
	}
}

// This will find our missile's target
void AMissile::FindPlayer()
{
	class UWorld* const world = GetWorld();

	if (world)
	{
		for (TActorIterator<ADemoCharacter> ObstacleItr(world); ObstacleItr; ++ObstacleItr)
		{
			FName PlayerTagName = FName(TEXT("Player"));
			class ADemoCharacter* FoundPlayer = *ObstacleItr;

			if (FoundPlayer != nullptr)
			{
				if (FoundPlayer->ActorHasTag(PlayerTagName))
				{
					if (PlayerInWorld != FoundPlayer)
					{
						PlayerInWorld = FoundPlayer;
					}
				}
			}
		}
	}
}

// Once our delay has finished, we search for possible targets
void AMissile::UpdateTarget()
{
	if (!hasTargetPosition)
	{
		if (PlayerInWorld != NULL)
		{
			if (PlayerInWorld->IsValidLowLevel())
			{
				target = PlayerInWorld;
				hasTargetPosition = true;
				hasNoTarget = false;

				// Keep Our Mesh Rotation Offset
				FRotator rotVal = MissileMesh->GetComponentRotation();
				rotVal.Roll = 0.f;
				rotVal.Pitch = -90.f;
				rotVal.Yaw = 0.f;
				MissileMesh->SetRelativeRotation(rotVal);
			}
			else
			{
				target = nullptr;
				hasTargetPosition = true;
				hasNoTarget = true;
			}
		}
		else
		{
			target = nullptr;
			hasTargetPosition = true;
			hasNoTarget = true;
		}
	}
}

// Allow 1 second to pass before finding our target
void AMissile::DelayLogic(float dTime)
{
	if (!hasFinishedDelay)
	{
		delayTimer += 1 * dTime;

		if (delayTimer > 1.f)
		{
			UpdateTarget();
			this->SetActorEnableCollision(true);
			hasFinishedDelay = true;
		}
	}
}
#pragma endregion

// Called every frame
void AMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!hasFinishedDelay)
	{
		DelayLogic(DeltaTime);
	}
	else
	{
		// If a target is found, move the missile actor toward target
		if (hasTargetPosition)
		{
			if (target != NULL)
			{
				if (target->IsValidLowLevel())
				{
					FVector wantedDir = (target->GetActorLocation() - GetActorLocation()).GetSafeNormal();
					wantedDir += target->GetVelocity() * wantedDir.Size() / 200.f;
					ProjectileMovement->Velocity += wantedDir * 200.f * DeltaTime;
					ProjectileMovement->Velocity = ProjectileMovement->Velocity.GetSafeNormal() * 200.f;
					
					temp +=1.0f * DeltaTime;
					ProjectileMovement->ProjectileGravityScale = temp;
					
					
				}
				else
				{
					if (!this->IsPendingKill())
						if (this->IsValidLowLevel())
							K2_DestroyActor();
				}
			}
			else
			{
				// If a target is NOT found, continue to move the missile actor upwards
				if (hasNoTarget)
				{
					ProjectileMovement->Velocity = GetActorUpVector() * 200.f;
					hasNoTarget = false;
				}
			}
		}

		// Destroy the missile actor after a 15 Second countdown
		lifetimeCountdown -= 1 * DeltaTime;

		if (lifetimeCountdown < 0.f)
		{
			if (!canBeDestroyed)
			{
				canBeDestroyed = true;
				target = nullptr;
				Explode();
			}
		}
	}
}

void AMissile::Explode()
{
	PlayExplosion(ExplosionSystem);
	PlayExplosionSound(ExplosionSound);

	if (this->IsValidLowLevel())
		Destroy();
}

void AMissile::OnOverlapBegin(UPrimitiveComponent * overlappedComp, AActor * otherActor, UPrimitiveComponent * otherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & hitResult)
{
	ADemoCharacter* Characher = Cast<ADemoCharacter>(otherActor);
	if (Characher) {
		Destroy();
	}

}


UParticleSystemComponent * AMissile::PlayExplosion(UParticleSystem * explosion)
{
	return nullptr;
}

UAudioComponent * AMissile::PlayExplosionSound(USoundCue * sound)
{
	return nullptr;
}

