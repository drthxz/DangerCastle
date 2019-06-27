// Fill out your copyright notice in the Description page of Project Settings.

#include "AI_Controller.h"

#include "AI_Character.h"
#include "AIPatrolNode.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"

#include "Kismet/GameplayStatics.h"
#include "DemoCharacter.h"
#include "AI/AIPatrolNode.h"


AAI_Controller::AAI_Controller()
{
	//Initialize blackboard and behavior tree
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlckaboardComp"));

	//Initialie blackboard keys
	PlayerKey = "Target";
	LocationToGoKey = "LocationToGo";

	CurrentPoint = 0;

}


void AAI_Controller::Possess(APawn * Pawn)
{
	Super::Possess(Pawn);

	//Get reference to the character
	AAI_Character* AICharater = Cast<AAI_Character>(Pawn);

	if (AICharater) {

		if (AICharater->BehaviorTree->BlackboardAsset) {

			BlackboardComp->InitializeBlackboard(*(AICharater->BehaviorTree->BlackboardAsset));


		}

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAIPatrolNode::StaticClass(), TargetPoints);

		BehaviorComp->StartTree(*AICharater->BehaviorTree);
	}



}

void AAI_Controller::SetPlayerCaught(APawn * Pawn)
{
	ADemoCharacter* Player = Cast<ADemoCharacter>(Pawn);

	
	if (BlackboardComp) {


		BlackboardComp->SetValueAsObject(PlayerKey, Pawn);
		bIsFind = true;
		
		//MoveToActor(Player);
	}

}


