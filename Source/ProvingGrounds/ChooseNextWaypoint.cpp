// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrollingGuard.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	auto Blackboard = OwnerComp.GetBlackboardComponent();
	auto AiController = OwnerComp.GetAIOwner();
	auto ControlledPawn = AiController->GetPawn();
	auto PatrollingGuard = Cast<APatrollingGuard>(ControlledPawn);
	auto PatrollPointsC = PatrollingGuard->PatrolPointsC;

	auto Index = Blackboard->GetValueAsInt(IndexKey.SelectedKeyName);
	UE_LOG(LogTemp, Warning, TEXT("Index value:%i"),Index);

	Blackboard->SetValueAsObject(WaypointKey.SelectedKeyName, PatrollPointsC[Index]);
	

	Blackboard->SetValueAsInt(IndexKey.SelectedKeyName, ((Index + 1) % (PatrollPointsC.Num())));
	return EBTNodeResult::Succeeded;
}
