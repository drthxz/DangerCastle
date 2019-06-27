// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"

#include "SetBomb.generated.h"

UCLASS()
class DEMO_API ASetBomb : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASetBomb();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bomb")
		USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bomb")
		UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bomb")
		UStaticMeshComponent* MeshCmp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bomb")
		UStaticMeshComponent* Fire_Piston;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bomb")
		bool bIsPut = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bomb")
		bool bIsfont = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bomb")
		UTextRenderComponent* TextRender;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void MakeTextFacePlayer();
	
};
