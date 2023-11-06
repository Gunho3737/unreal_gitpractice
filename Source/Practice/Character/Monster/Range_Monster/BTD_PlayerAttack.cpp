// Fill out your copyright notice in the Description page of Project Settings.


#include "BTD_PlayerAttack.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "../Monster_Base.h"

UBTD_PlayerAttack::UBTD_PlayerAttack()
{
	m_TargetKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTD_PlayerAttack, m_TargetKey), AActor::StaticClass());
	m_RangeKey.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(UBTD_PlayerAttack, m_RangeKey));
}

bool UBTD_PlayerAttack::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{

	// ���� üũ�� Ÿ���� �����´�.
// Ÿ���� m_TargetKey �� ����Ǿ��ִ� �����忡�� �����´�.
	if (m_TargetKey.IsNone())
	{
		// ������ Ű�� ������ �ȵǾ������� ����üũ�� ����� �� �� �����Ƿ� ����ó���� �Ѵ�.
		return false;
	}

	// �����忡 Target �� null �̶��(���� ��ã�Ҵٸ�)
	UObject* pObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(m_TargetKey.SelectedKeyName);
	if (!IsValid(pObject))
	{
		return false;
	}

	AActor* pTarget = Cast<AActor>(pObject);

	// �⺻������ m_Range �� �ִ� ���� ������ ����Ѵ�.
	float fRange = m_Range;
	if (!m_RangeKey.IsNone())
	{
		// m_RangeKey �� �������� �����ϰ��ִ� ������Ű�� ����Ǿ�������
		// �ش� ���� �����忡�� �����ͼ� ������ ����Ѵ�.
		fRange = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(m_RangeKey.SelectedKeyName);
	}

	//���� �ִϸ��̼��� ������̶�� ����üũ ���� �ٷ� true�� ������
	if (true == OwnerComp.GetBlackboardComponent()->GetValueAsBool(FName("IsAttackAnimationPlay")))
	{
		return true;
	}

	// �÷��̾ �����ȿ� �ִ��� üũ�Ѵ�.
	AAIController* pController = OwnerComp.GetAIOwner();
	AMonster_Base* pMonster = Cast<AMonster_Base>(pController->GetPawn());

	if (IsValid(pMonster))
	{
		float Distance = FVector::Distance(pTarget->GetActorLocation(), pMonster->GetActorLocation());
		if (Distance < fRange)
		{
			return true;
		}
	}

	return false;
}
