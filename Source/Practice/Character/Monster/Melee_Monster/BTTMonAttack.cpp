// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTMonAttack.h"
#include "../Monster_Base.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "../../../FPSPopol/Player/FPSPlayer.h"

UBTTMonAttack::UBTTMonAttack()
{
}

EBTNodeResult::Type UBTTMonAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AMonster_Base* pMonster = Cast<AMonster_Base>(OwnerComp.GetAIOwner()->GetPawn());

	if (IsValid(pMonster) == false)
	{
		//오너가 없으면 리턴
		return EBTNodeResult::Failed;
	}


	switch (pMonster->GetMonsterType())
	{
	case EMON_TYPE::MELEE:
		{
			pMonster->ChangeState(EMON_STATE::MELEE_ATTACK);
		}
		break;
	case EMON_TYPE::RANGE:
		{
			pMonster->ChangeState(EMON_STATE::RANGE_ATTACK);
		}
		break;
	case EMON_TYPE::BOSS:
		{
			pMonster->ChangeState(EMON_STATE::MELEE_ATTACK);
		}
		break;
	default:
		break;
	}

	return EBTNodeResult::Succeeded;
}
