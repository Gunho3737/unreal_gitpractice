// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "behaviortree/BehaviorTree.h"
#include "behaviortree/blackboarddata.h"
#include "behaviortree/blackboardcomponent.h"

#include "AIController_Range.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API AAIController_Range : public AAIController
{
	GENERATED_BODY()

public:
	//���� ���� ������ ��µǴ� �Լ�
	virtual void OnPossess(APawn* _Owner) override;

	//���� ������ ������ ��µǴ� �Լ�
	virtual void OnUnPossess() override;

private:
	// ����� �ൿƮ��	
	UBehaviorTree* m_BehaviorTree;

	// ����� ������	
	UBlackboardData* m_Blackboard;
};
