// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTMonTrace.h"
#include "AIController.h"
#include "../Monster_Base.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "../../../Header/GlobalHeader.h"

UBTTMonTrace::UBTTMonTrace()
{
	bNotifyTick = true;

	m_TargetKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTMonTrace, m_TargetKey), AActor::StaticClass());
	m_RecentTargetPos.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTMonTrace, m_RecentTargetPos));
}

EBTNodeResult::Type UBTTMonTrace::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	// 추적대상을 블랙보드 키에서 설정을 안해놨으면 Task 실패
	if (m_TargetKey.IsNone() || m_RecentTargetPos.IsNone())
	{
		return EBTNodeResult::Failed;
	}

	// 행동 시킬 AIController 를 가져온다.
	AAIController* pController = OwnerComp.GetAIOwner();

	// 추적 대상을 알아낸다(블랙보드 키)
	ACharacter* pCharacter = Cast<ACharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(m_TargetKey.SelectedKeyName));

	// 추적 대상이 캐릭터가 아니라면 실패
	if (!IsValid(pCharacter))
	{
		return EBTNodeResult::Failed;
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName("TraceTarget"), pCharacter);
	}


	// 네비메시가 깔려있는 곳에서 목적지를 향해 길찾기를 통한 이동
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(pController, pCharacter->GetActorLocation());

	// 현재 추적대상의 위치(최근 이동 목적지) 를 블랙보드에 기록해둔다.
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(m_RecentTargetPos.SelectedKeyName, pCharacter->GetActorLocation());


	// 추적상태에 들어오면 몬스터를 이동상태로 만들어줌
	AMonster_Base* pMonster = Cast<AMonster_Base>(pController->GetPawn());
	pMonster->ChangeState(EMON_STATE::MOVE);

	return EBTNodeResult::InProgress;
}


void UBTTMonTrace::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	// 추적대상을 블랙보드 키에서 설정을 안해놨으면 Task 실패
	if (m_TargetKey.IsNone() || m_RecentTargetPos.IsNone())
	{
		// InProgress 상태를 중단함
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	// 추적중에 추적대상이 공격범위안으로 들어오면, 추적 상태를 성공으로 중단시켜서
	// 트리가 다시 루트부터 시작될 수 있도록 한다.
	ACharacter* pTarget = Cast<ACharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("TraceTarget")));
	if (!IsValid(pTarget))
	{
		// InProgress 상태를 중단함
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	// 몬스터의 공격범위
	float fAttRange = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(L"AttackRange");

	AAIController* pController = OwnerComp.GetAIOwner();
	AMonster_Base* pMonster = Cast<AMonster_Base>(pController->GetPawn());
	if (!IsValid(pMonster))
	{
		// InProgress 상태를 중단함
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	// 몬스터와 타겟 사이의 거리
	float Distance = FVector::Distance(pTarget->GetActorLocation(), pMonster->GetActorLocation());

	// 몬스터와 타겟사이의 거리가 공격범위 안이면
	if (Distance < fAttRange)
	{
		// 성공으로 반환해서, 행동트리가 Patrol 로 가는것을 막음
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}

	FVector vRecentDest = OwnerComp.GetBlackboardComponent()->GetValueAsVector(m_RecentTargetPos.SelectedKeyName);

	// 현재 타겟의 위치가, 몬스터의 이동 목적지와 재평가거리 이상 멀어지면
	if (m_RevaluateRange < FVector::Distance(pTarget->GetActorLocation(), vRecentDest))
	{
		// 현재 타겟의 위치로 다시 길찾기를 시도한다.		
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(pController, pTarget->GetActorLocation());

		// 현재 추적대상의 위치(최근 이동 목적지) 를 블랙보드에 기록해둔다.
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(m_RecentTargetPos.SelectedKeyName, pTarget->GetActorLocation());
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}
}