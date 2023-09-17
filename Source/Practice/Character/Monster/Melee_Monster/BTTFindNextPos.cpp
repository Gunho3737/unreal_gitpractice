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

	// 중심위치에서 반경범위내에 랜덤한 위치를 가져온다.
	FNavLocation location;
	UNavigationSystemV1* pNaviSys = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	pNaviSys->GetRandomPointInNavigableRadius(vInitPos, m_RangeFromCenter, location);

	FVector vNextPos = location.Location;

	// 찾은 다음 이동위치를 NextPosKey 에 세팅된 블랙보드키에 저장시킨다.
	if (m_NextPosKey.IsNone())
	{
		return EBTNodeResult::Failed;
	}

	// 몬스터의 상태를 이동상태로 변경한다.
	AMonster_Base* pMonster = Cast<AMonster_Base>(OwnerComp.GetAIOwner()->GetPawn());
	if (IsValid(pMonster))
	{
		pMonster->ChangeState(EMON_STATE::MOVE);
	}

	// 다음 이동할 위치를 블랙보드에 기록한다.
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(m_NextPosKey.SelectedKeyName, vNextPos);
	return EBTNodeResult::Succeeded;
}