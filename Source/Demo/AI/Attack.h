// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "DemoCharacter.h"
#include "Attack.generated.h"


UCLASS()
class DEMO_API AAttack : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAttack();



public:	
	
	UPROPERTY(EditAnywhere)
		UBoxComponent* MyBoxComponent;

	//UPROPERTY(EditAnywhere)
	//	UParticleSystemComponent* Fire;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UDamageType> AttackDamageType;

	UPROPERTY(EditAnywhere)
		ADemoCharacter* MyCharacter;
		//AActor* MyCharacter;

	UPROPERTY(EditAnywhere)
		FHitResult MyHit;

	bool bCanApplyDamage;
	FTimerHandle TimeHandle;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void ApplyAttackDamage();
	
};
