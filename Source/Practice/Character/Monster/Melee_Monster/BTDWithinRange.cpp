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
	// 범위 체크할 타겟을 가져온다.
	// 타겟을 m_TargetKey 에 연결되어있는 블랙보드에서 가져온다.
	if (m_TargetKey.IsNone())
	{
		// 블랙보드 키가 연결이 안되어있으면 범위체크할 대상을 알 수 없으므로 실패처리를 한다.
		return false;
	}
	
	// 블랙보드에 Target 이 null 이라면(아직 못찾았다면)
	UObject* pObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(m_TargetKey.SelectedKeyName);
	if (!IsValid(pObject))
	{
		return false;
	}
	
	AActor* pTarget = Cast<AActor>(pObject);
	
	// 기본적으루 m_Range 에 있는 값을 범위로 사용한다.
	float fRange = m_Range;
	if (!m_RangeKey.IsNone())
	{
		// m_RangeKey 에 범위값을 저장하고있는 블랙보드키가 연결되어있으면
		// 해당 값을 블랙보드에서 가져와서 범위로 사용한다.
		fRange = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(m_RangeKey.SelectedKeyName);
	}
	
	
	// 플레이어가 범위안에 있는지 체크한다.
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
