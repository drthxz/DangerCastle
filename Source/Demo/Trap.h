// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"

#include "DemoCharacter.h"
#include "Trap.generated.h"


/**
 * 
 */
UCLASS()
class DEMO_API ATrap : public ATriggerBox
{
	GENERATED_BODY()


protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:


	ATrap();

	UFUNCTION()
		void OnOverlapBegin(class AActor* OverlappedAtcor, class AActor* OtherActor);

	UFUNCTION()
		void OnOverlapEnd(class AActor* OverlappedAtcor, class AActor* OtherActor);

	UPROPERTY(EditAnywhere)
		class AActor* SpecificActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Trap")
		bool bIsTrap;

	UFUNCTION()
		bool getIsTrap();

	UFUNCTION()
		void setbIsTrap(bool trap);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Trap")
		bool bIsTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Trap")
		float time;

	UPROPERTY(EditAnywhere)
		ADemoCharacter* Character;



};
