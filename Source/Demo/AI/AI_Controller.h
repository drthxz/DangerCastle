// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "AI_Controller.generated.h"



/**
 * 
 */
UCLASS()
class DEMO_API AAI_Controller : public AAIController
{
	GENERATED_BODY()

public:

	AAI_Controller();

	int32 CurrentWaypoint = 0;

	//Behavior tree component
	class UBehaviorTreeComponent* BehaviorComp;

	//Our blackboard component
	class UBlackboardComponent* BlackboardComp;
	
	//Blackboard keys
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName LocationToGoKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		FName PlayerKey;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
		TArray<AActor*> TargetPoints;


	int32 CurrentPoint = 0;

	virtual void Possess(APawn* Pawn) override;



	void SetPlayerCaught(APawn* Pawn);

	//Inline getter functions
	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
	FORCEINLINE UBehaviorTreeComponent* GetBehaviorTreeComp() { return BehaviorComp; }

	FORCEINLINE TArray<AActor*> GetTargetPoints() { return TargetPoints; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		bool bIsFind = false;
};