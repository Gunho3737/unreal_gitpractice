// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "../../../Header/GlobalHeader.h"
#include "BTTMonAttack.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API UBTTMonAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTMonAttack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

};
