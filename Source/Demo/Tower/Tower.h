// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "TimerManager.h"
#include "Components/TimelineComponent.h"

#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Tower.generated.h"


UCLASS()
class DEMO_API ATower : public AActor
{
	GENERATED_BODY()

private:
	// Timer Handle for Repeating Missile Fire
	FTimerHandle MissileHandle;
	FTimerHandle MemberTimerHandle;
	
public:	
	// Sets default values for this actor's properties
	ATower(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Collision Component for Turret Class
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USceneComponent* Root;


	// Static Mesh Component for Turret Class
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		UStaticMeshComponent* TowerMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		UStaticMeshComponent* TowerMesh_up;
	

	//Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float Health;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
	int32 getcount = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
		float HealthPercentage;

	UTimelineComponent* MyTimeline;



public:

	//Health
	UFUNCTION(BlueprintPure, Category = "Health")
		float GetHealth();

	UFUNCTION(BlueprintPure, Category = "Health")
		FText GetHealthIntText();
	
	UFUNCTION()
		void DamageTimer();

	UFUNCTION()
		void SetDamageState();

	UFUNCTION(BlueprintCallable, Category = "Health")
		void RecievePointDamage(float Damage,
			const class UDamageType * DamageType,
			FVector HitLocation,
			FVector HitNormal,
			class UPrimitiveComponent * HitComponent,
			FName BoneName,
			FVector ShotFromDirection,
			class AController * InstigatedBy,
			AActor * DamageCauser,
			const FHitResult & HitInfo);

	UFUNCTION(BlueprintCallable, Category = "Health")
		void UpdateHealth(float HealthChange);

};
