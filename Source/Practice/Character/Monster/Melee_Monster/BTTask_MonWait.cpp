// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MonWait.h"

#include "AIController.h"
#include "../Monster_Base.h"

EBTNodeResult::Type UBTTask_MonWait::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// ������ ���¸� Idle ���·� ����
	AMonster_Base* pMonster = Cast<AMonster_Base>(OwnerComp.GetAIOwner()->GetPawn());

	if (IsValid(pMonster))
	{
		pMonster->ChangeState(EMON_STATE::IDLE);
	}

	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
