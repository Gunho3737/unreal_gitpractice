// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController_Range.h"
#include "../Monster_Base.h"

void AAIController_Range::OnPossess(APawn* _Owner)
{
	Super::OnPossess(_Owner);

	AMonster_Base* pMonster = Cast<AMonster_Base>(_Owner);

	if (!IsValid(pMonster))
	{
		//���� ����� ���Ͱ� �ƴҽ� ����
		return;
	}

	// ���� ���(����) �� ����, ����� �ൿƮ���� �����´�.
	m_BehaviorTree = pMonster->GetBehaviorTree();
	m_Blackboard = pMonster->GetBloackboard();

	if (IsValid(m_Blackboard))
	{
		// AIController �� ó������ Blackboad ������Ʈ�� ������ �ִ°��� �ƴ�
		// UseBlackboard �Լ��� blackboard �� �����ϸ�, �׶� ���ο��� BlackboardComponent �� ����
		UBlackboardComponent* pCom = nullptr;
		UseBlackboard(m_Blackboard, pCom);

		if (IsValid(m_BehaviorTree))
		{
			// BehaviorTree �� �����ϴ� Blackboard �� Useblackboard �Լ��� ������ Blackboard �� ���� �ٸ���
			// BehaviorTree ���� �����ϴ� Blackboard �� �켱������ �� ����
			// RunBehaviorTree �Լ� �ȿ��� BehaviorTreeComponent �� �����ȴ�.
			RunBehaviorTree(m_BehaviorTree);
		}
	}

}

void AAIController_Range::OnUnPossess()
{
	Super::OnUnPossess();
}
