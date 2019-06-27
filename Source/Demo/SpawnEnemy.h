// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "DemoCharacter.h"

#include "SpawnEnemy.generated.h"



UCLASS()
class DEMO_API ASpawnEnemy : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	ASpawnEnemy();

	UPROPERTY(EditAnywhere, Category = "AI")
		TSubclassOf<class AAI_Character> ToSpawn;

	UPROPERTY(EditAnywhere, Category = "AI")
		TSubclassOf<class APawn> ToSpawn_BP;


	UFUNCTION(BlueprintCallable)
		void Spawn();

	float currentTime;

	UPROPERTY(EditAnywhere, Category = "AI")
		bool trap;



	UPROPERTY(EditAnywhere)
		ADemoCharacter* Character;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*UFUNCTION()
		void OnOverlapBegin(class AActor* OverlappedAtcor, class AActor* OtherActor);*/

	
};
