// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../Header/GlobalHeader.h"

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDMonsterDeathCheck.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API UBTDMonsterDeathCheck : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDMonsterDeathCheck();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
