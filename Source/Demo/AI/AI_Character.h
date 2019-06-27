// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AI_Character.generated.h"

class UTimelineComponent;

UCLASS()
class DEMO_API AAI_Character : public ACharacter
{
	GENERATED_BODY()


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	AAI_Character();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "AI")
		class UBehaviorTree* BehaviorTree;
	
	UPROPERTY(VisibleAnywhere, Category = "AI")
		class UPawnSensingComponent* PawnSensingComp;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float HealthPercentage;

	UTimelineComponent* MyTimeline;
	struct FTimerHandle MemberTimerHandle;

	


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

private:

	UFUNCTION()
		void OnPlayerCaught(APawn* Pawn);



};
