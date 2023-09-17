// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTFindNextPos.h"

#include "../Monster_Base.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "AIController.h"

UBTTFindNextPos::UBTTFindNextPos()
{
	m_CenterPosKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTFindNextPos, m_CenterPosKey));
	m_NextPosKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTFindNextPos, m_NextPosKey));
}


EBTNodeResult::Type UBTTFindNextPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (m_CenterPosKey.IsNone())
		return EBTNodeResult::Failed;

	FVector vInitPos = OwnerComp.GetBlackboardComponent()->GetValueAsVector(m_CenterPosKey.SelectedKeyName);

	// �߽���ġ���� �ݰ�������� ������ ��ġ�� �����´�.
	FNavLocation location;
	UNavigationSystemV1* pNaviSys = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	pNaviSys->GetRandomPointInNavigableRadius(vInitPos, m_RangeFromCenter, location);

	FVector vNextPos = location.Location;

	// ã�� ���� �̵���ġ�� NextPosKey �� ���õ� ������Ű�� �����Ų��.
	if (m_NextPosKey.IsNone())
	{
		return EBTNodeResult::Failed;
	}

	// ������ ���¸� �̵����·� �����Ѵ�.
	AMonster_Base* pMonster = Cast<AMonster_Base>(OwnerComp.GetAIOwner()->GetPawn());
	if (IsValid(pMonster))
	{
		pMonster->ChangeState(EMON_STATE::MOVE);
	}

	// ���� �̵��� ��ġ�� �����忡 ����Ѵ�.
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(m_NextPosKey.SelectedKeyName, vNextPos);
	return EBTNodeResult::Succeeded;
}