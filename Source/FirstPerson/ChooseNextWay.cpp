// Fill out your copyright notice in the Description page of Project Settings.


#include "ChooseNextWay.h"
#include "PatrolRoute.h"
#include"AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChooseNextWay:: ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//get patrol points
	auto AIComponent = OwnerComp.GetAIOwner();
	auto ControlledPawn = AIComponent->GetPawn();
	auto PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();
	if (!ensure(PatrolRoute)){ return EBTNodeResult::Failed; }	
	
	auto PatrolPoints = PatrolRoute->GetPatrolPoints();
	if(PatrolPoints.Num()==NULL) { UE_LOG(LogTemp, Warning, TEXT("no patrolpoints found")) }

	//Set next way points
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(WayPointKey.SelectedKeyName, PatrolPoints[Index]);

	//cycle Waypoint
	auto NextIndex = (Index + 1) % (PatrolPoints.Num());
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);

		return EBTNodeResult::Succeeded;
	
}

