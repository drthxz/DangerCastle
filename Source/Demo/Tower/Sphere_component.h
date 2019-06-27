// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DemoCharacter.h"
#include "TimerManager.h"
#include "Components/TimelineComponent.h"

#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"

#include "Sphere_component.generated.h"

UCLASS()
class DEMO_API ASphere_component : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ASphere_component();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UCapsuleComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		class UStaticMeshComponent* Cube_Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Target")
		class ADemoCharacter* Characher;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Target")
		bool Targetlocked;
	

	UFUNCTION()
		void UpdateTargetRotation();

	UFUNCTION()
		void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	
};
