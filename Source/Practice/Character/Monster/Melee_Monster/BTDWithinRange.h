// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../Header/GlobalHeader.h"

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDWithinRange.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API UBTDWithinRange : public UBTDecorator
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Data", meta = (AllowPrivateAccess = true))
	float	m_Range;

	UPROPERTY(EditAnywhere, Category = "Blackboard", meta = (AllowPrivateAccess = true))
	FBlackboardKeySelector	m_TargetKey;

	UPROPERTY(EditAnywhere, Category = "Blackboard", meta = (AllowPrivateAccess = true))
	FBlackboardKeySelector	m_RangeKey;



public:
	UBTDWithinRange();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
