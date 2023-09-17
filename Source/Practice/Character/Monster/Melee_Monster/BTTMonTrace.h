// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTMonTrace.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API UBTTMonTrace : public UBTTaskNode
{
	GENERATED_BODY()

private:
	// ���� ���
	UPROPERTY(EditAnywhere, Category = "Blackboard", meta = (AllowPrivateAccess = true))
	FBlackboardKeySelector	m_TargetKey;

	// �̵� ������
	UPROPERTY(EditAnywhere, Category = "Blackboard", meta = (AllowPrivateAccess = true))
	FBlackboardKeySelector	m_RecentTargetPos;

	// ���� �� ������ �ߴ��ϱ� ���� ���� �Ÿ�
	UPROPERTY(EditAnywhere, Category = "Blackboard", meta = (AllowPrivateAccess = true))
	float					m_RevaluateRange;


public:
	UBTTMonTrace();

public:
	// Task ���� �� ȣ��
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	// Task �� InProgress ���¸� �� ƽ���� ȣ��
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
