// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTMonAttack.h"
#include "../Monster_Base.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UBTTMonAttack::UBTTMonAttack()
{
}

EBTNodeResult::Type UBTTMonAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AMonster_Base* pMonster = Cast<AMonster_Base>(OwnerComp.GetAIOwner()->GetPawn());
	if (IsValid(pMonster))
	{
		//pMonster->GetMonsterInfo()

		pMonster->ChangeState(EMON_STATE::MELEE_ATTACK);
	}
	return EBTNodeResult::Succeeded;
}
