// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTMonsterDeathTask.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API UBTTMonsterDeathTask : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	float time;


public:
	UBTTMonsterDeathTask();

public:
	// Task ���� �� ȣ��
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	// Task �� InProgress ���¸� �� ƽ���� ȣ��
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
