// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTaskMove.h"

#include "AI_Controller.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "AIPatrolNode.h"

#include "DemoCharacter.h"

EBTNodeResult::Type UBTTaskMove::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);


	AAI_Controller* AICon = Cast<AAI_Controller>(OwnerComp.GetAIOwner());


	if (AICon)
	{

		UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();
		AAIPatrolNode* CurrentPoint = Cast<AAIPatrolNode>(BlackboardComp->GetValueAsObject("LocationToGo"));

		TArray<AActor*> Points = AICon->GetTargetPoints();

		//This variable will contain a random index in order to determine the next possible point
		int32 RandomIndex;

		//Here, we store the possible next target point
		AAIPatrolNode* NextPoint = nullptr;

		if (CurrentPoint) {
			//Find a next point which is different from the current one
			do
			{
				RandomIndex = FMath::RandRange(0, Points.Num() - 1);
				//Remember that the Array provided by the Controller function contains AActor* objects so we need to cast.
				NextPoint = Cast<AAIPatrolNode>(Points[RandomIndex]);
			} while (CurrentPoint == NextPoint);

			//Update the next location in the Blackboard so the bot can move to the next Blackboard value
			BlackboardComp->SetValueAsObject("LocationToGo", CurrentPoint);
			
			//At this point, the task has been successfully completed
			return EBTNodeResult::Succeeded;
		}
		
	}
	return EBTNodeResult::Failed;
}
