// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "behaviortree/BehaviorTree.h"
#include "behaviortree/blackboarddata.h"
#include "behaviortree/blackboardcomponent.h"

#include "AIController_Melee.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API AAIController_Melee : public AAIController
{
	GENERATED_BODY()

private:
	// 사용할 행동트리	
	UBehaviorTree* m_BehaviorTree;

	// 사용할 블랙보드	
	UBlackboardData* m_Blackboard;


public:
	//빙의 시작 시점에 출력되는 함수
	virtual void OnPossess(APawn* _Owner) override;

	//빙의 끝나는 시점에 출력되는 함수
	virtual void OnUnPossess() override;
};
