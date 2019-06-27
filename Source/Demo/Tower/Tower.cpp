// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"
#include "Missile.h"
#include "Engine/World.h"
#include "Engine/GameEngine.h"




// Sets default values
ATower::ATower(const FObjectInitializer& ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(Root);
	
	TowerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TowerMesh"));
	TowerMesh->SetupAttachment(GetRootComponent());

	TowerMesh_up = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TowerMesh_up"));
	TowerMesh_up->SetupAttachment(TowerMesh);

}

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();
	
	//MaxHealth = 10000.0f;
	Health = MaxHealth;
	HealthPercentage = 1.0f;

	bCanBeDamaged = true;

}


float ATower::GetHealth()
{
	return HealthPercentage;
}

FText ATower::GetHealthIntText()
{
	int32 HP = FMath::RoundHalfFromZero(HealthPercentage * 100);
	FString HPS = FString::FromInt(HP);
	FString HealthHUD = HPS + FString(TEXT("%"));
	FText HPText = FText::FromString(HealthHUD);

	return HPText;
}

void ATower::DamageTimer()
{
	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &ATower::SetDamageState, 2.0f, false);
}

void ATower::SetDamageState()
{
	bCanBeDamaged = true;
}

void ATower::RecievePointDamage(float Damage, const UDamageType * DamageType, FVector HitLocation, FVector HitNormal, UPrimitiveComponent * HitComponent, FName BoneName, FVector ShotFromDirection, AController * InstigatedBy, AActor * DamageCauser, const FHitResult & HitInfo)
{
	bCanBeDamaged = false;
	UpdateHealth(-Damage);
	DamageTimer();
}

void ATower::UpdateHealth(float HealthChange)
{
	Health += HealthChange;
	Health = FMath::Clamp(Health, 0.0f, MaxHealth);
	HealthPercentage = Health / MaxHealth;
}
