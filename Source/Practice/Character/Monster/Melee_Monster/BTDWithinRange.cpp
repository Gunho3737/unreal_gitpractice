// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDWithinRange.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "../Monster_Base.h"

UBTDWithinRange::UBTDWithinRange()
{
	m_TargetKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTDWithinRange, m_TargetKey), AActor::StaticClass());
	m_RangeKey.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(UBTDWithinRange, m_RangeKey));
}

bool UBTDWithinRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
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
