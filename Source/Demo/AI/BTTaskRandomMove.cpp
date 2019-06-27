// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTaskRandomMove.h"

#include "AI_Controller.h"

#include "BehaviorTree/BlackboardComponent.h"

#include "DemoCharacter.h"
#include "NavigationSystem/Public/NavigationSystem.h"

EBTNodeResult::Type UBTTaskRandomMove::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAI_Controller* AICon = Cast<AAI_Controller>(OwnerComp.GetAIOwner());
	UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();

	if (AICon)
	{
		FNavLocation RandomPoint;
		UNavigationSystemV1* NavSystem = Cast<UNavigationSystemV1>(GetWorld()->GetNavigationSystem());

		if (NavSystem->GetRandomPointInNavigableRadius(AICon->GetPawn()->GetActorLocation(), 500.0f, RandomPoint)) {

			AICon->MoveTo(RandomPoint.Location);

			return EBTNodeResult::Succeeded;
		}


	}

		return EBTNodeResult::Failed;
	

}
