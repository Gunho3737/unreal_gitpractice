// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDMonsterDeathCheck.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Monster_Base.h"
#include "AIController.h"


UBTDMonsterDeathCheck::UBTDMonsterDeathCheck()
{
}

bool UBTDMonsterDeathCheck::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	float curhp = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(TEXT("CurHP"));

	if (curhp < 0.0f)
	{
		AMonster_Base* pMonster = Cast<AMonster_Base>(OwnerComp.GetAIOwner()->GetPawn());

		if (IsValid(pMonster))
		{
			pMonster->ChangeState(EMON_STATE::DEAD);
			return true;
		}
	}

	return false;
}
