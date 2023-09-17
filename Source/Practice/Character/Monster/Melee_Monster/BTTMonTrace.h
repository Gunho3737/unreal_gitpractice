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
	// 추적 대상
	UPROPERTY(EditAnywhere, Category = "Blackboard", meta = (AllowPrivateAccess = true))
	FBlackboardKeySelector	m_TargetKey;

	// 이동 목적지
	UPROPERTY(EditAnywhere, Category = "Blackboard", meta = (AllowPrivateAccess = true))
	FBlackboardKeySelector	m_RecentTargetPos;

	// 추적 중 추적을 중단하기 위한 재평가 거리
	UPROPERTY(EditAnywhere, Category = "Blackboard", meta = (AllowPrivateAccess = true))
	float					m_RevaluateRange;


public:
	UBTTMonTrace();

public:
	// Task 진입 시 호출
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	// Task 가 InProgress 상태면 매 틱마다 호출
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
