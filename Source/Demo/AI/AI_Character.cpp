// Fill out your copyright notice in the Description page of Project Settings.

#include "AI_Character.h"
#include "AI_Controller.h"

#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"

#include "Kismet/KismetMaterialLibrary.h"
#include "TimerManager.h"
#include "Components/TimelineComponent.h"


// Sets default values
AAI_Character::AAI_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Initialize senses
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->SetPeripheralVisionAngle(90.0f);
	
}

// Called when the game starts or when spawned
void AAI_Character::BeginPlay()
{
	Super::BeginPlay();
	
	if (PawnSensingComp) {

		PawnSensingComp->OnSeePawn.AddDynamic(this, &AAI_Character::OnPlayerCaught);
	}

	//MaxHealth = 1000.0f;
	//Health = MaxHealth;
	//HealthPercentage = 1.0f;
	bCanBeDamaged = true;
}

// Called every frame
void AAI_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MyTimeline != nullptr) MyTimeline->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, nullptr);
}

// Called to bind functionality to input
void AAI_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AAI_Character::GetHealth()
{
	return HealthPercentage;
}

FText AAI_Character::GetHealthIntText()
{
	int32 HP = FMath::RoundHalfFromZero(HealthPercentage * 100);
	FString HPS = FString::FromInt(HP);
	FString HealthHUD = HPS + FString(TEXT("%"));
	FText HPText = FText::FromString(HealthHUD);
	return HPText;
}

void AAI_Character::DamageTimer()
{
	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &AAI_Character::SetDamageState, 2.0f, false);
}

void AAI_Character::SetDamageState()
{
	bCanBeDamaged = true;
}

void AAI_Character::RecievePointDamage(float Damage, const UDamageType * DamageType, FVector HitLocation, FVector HitNormal, UPrimitiveComponent * HitComponent, FName BoneName, FVector ShotFromDirection, AController * InstigatedBy, AActor * DamageCauser, const FHitResult & HitInfo)
{
	bCanBeDamaged = false;
	UpdateHealth(-Damage);
	DamageTimer();
}

void AAI_Character::UpdateHealth(float HealthChange)
{
	Health += HealthChange;
	Health = FMath::Clamp(Health, 0.0f, MaxHealth);
	HealthPercentage = Health / MaxHealth;
}

void AAI_Character::OnPlayerCaught(APawn * Pawn)
{
	//Get a reference to the player controller
	AAI_Controller* AIController = Cast<AAI_Controller>(GetController());

	if (AIController) {
		
		AIController->SetPlayerCaught(Pawn);
		
		
	}

}

