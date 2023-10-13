// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDMonsterDeathCheck.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDMonsterDeathCheck::UBTDMonsterDeathCheck()
{
}

bool UBTDMonsterDeathCheck::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	float curhp = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(TEXT("CurHP"));

	if (curhp < 0.0f)
	{
		return true;
	}

	return false;
}
