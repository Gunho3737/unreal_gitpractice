// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController_Range.h"
#include "../Monster_Base.h"

void AAIController_Range::OnPossess(APawn* _Owner)
{
	Super::OnPossess(_Owner);

	AMonster_Base* pMonster = Cast<AMonster_Base>(_Owner);

	if (!IsValid(pMonster))
	{
		//빙의 대상이 몬스터가 아닐시 리턴
		return;
	}

	// 빙의 대상(몬스터) 로 부터, 사용할 행동트리를 가져온다.
	m_BehaviorTree = pMonster->GetBehaviorTree();
	m_Blackboard = pMonster->GetBloackboard();

	if (IsValid(m_Blackboard))
	{
		// AIController 가 처음부터 Blackboad 컴포넌트를 가지고 있는것은 아님
		// UseBlackboard 함수에 blackboard 를 전달하면, 그때 내부에서 BlackboardComponent 를 만듬
		UBlackboardComponent* pCom = nullptr;
		UseBlackboard(m_Blackboard, pCom);

		if (IsValid(m_BehaviorTree))
		{
			// BehaviorTree 가 참조하는 Blackboard 와 Useblackboard 함수에 전달한 Blackboard 가 서로 다르면
			// BehaviorTree 에서 참조하는 Blackboard 의 우선순위가 더 높다
			// RunBehaviorTree 함수 안에서 BehaviorTreeComponent 가 생성된다.
			RunBehaviorTree(m_BehaviorTree);
		}
	}

}

void AAIController_Range::OnUnPossess()
{
	Super::OnUnPossess();
}
