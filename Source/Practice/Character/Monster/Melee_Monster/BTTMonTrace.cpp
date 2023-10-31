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

	// ��������� ������ Ű���� ������ ���س����� Task ����
	if (m_TargetKey.IsNone() || m_RecentTargetPos.IsNone())
	{
		return EBTNodeResult::Failed;
	}

	// �ൿ ��ų AIController �� �����´�.
	AAIController* pController = OwnerComp.GetAIOwner();

	// ���� ����� �˾Ƴ���(������ Ű)
	ACharacter* pCharacter = Cast<ACharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(m_TargetKey.SelectedKeyName));

	// ���� ����� ĳ���Ͱ� �ƴ϶�� ����
	if (!IsValid(pCharacter))
	{
		return EBTNodeResult::Failed;
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName("TraceTarget"), pCharacter);
	}


	// �׺�޽ð� ����ִ� ������ �������� ���� ��ã�⸦ ���� �̵�
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(pController, pCharacter->GetActorLocation());

	// ���� ��������� ��ġ(�ֱ� �̵� ������) �� �����忡 ����صд�.
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(m_RecentTargetPos.SelectedKeyName, pCharacter->GetActorLocation());


	// �������¿� ������ ���͸� �̵����·� �������
	AMonster_Base* pMonster = Cast<AMonster_Base>(pController->GetPawn());
	pMonster->ChangeState(EMON_STATE::MOVE);

	return EBTNodeResult::InProgress;
}


void UBTTMonTrace::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	// ��������� ������ Ű���� ������ ���س����� Task ����
	if (m_TargetKey.IsNone() || m_RecentTargetPos.IsNone())
	{
		// InProgress ���¸� �ߴ���
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	// �����߿� ��������� ���ݹ��������� ������, ���� ���¸� �������� �ߴܽ��Ѽ�
	// Ʈ���� �ٽ� ��Ʈ���� ���۵� �� �ֵ��� �Ѵ�.
	ACharacter* pTarget = Cast<ACharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("TraceTarget")));
	if (!IsValid(pTarget))
	{
		// InProgress ���¸� �ߴ���
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	// ������ ���ݹ���
	float fAttRange = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(L"AttackRange");

	AAIController* pController = OwnerComp.GetAIOwner();
	AMonster_Base* pMonster = Cast<AMonster_Base>(pController->GetPawn());
	if (!IsValid(pMonster))
	{
		// InProgress ���¸� �ߴ���
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	// ���Ϳ� Ÿ�� ������ �Ÿ�
	float Distance = FVector::Distance(pTarget->GetActorLocation(), pMonster->GetActorLocation());

	// ���Ϳ� Ÿ�ٻ����� �Ÿ��� ���ݹ��� ���̸�
	if (Distance < fAttRange)
	{
		// �������� ��ȯ�ؼ�, �ൿƮ���� Patrol �� ���°��� ����
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}

	FVector vRecentDest = OwnerComp.GetBlackboardComponent()->GetValueAsVector(m_RecentTargetPos.SelectedKeyName);

	// ���� Ÿ���� ��ġ��, ������ �̵� �������� ���򰡰Ÿ� �̻� �־�����
	if (m_RevaluateRange < FVector::Distance(pTarget->GetActorLocation(), vRecentDest))
	{
		// ���� Ÿ���� ��ġ�� �ٽ� ��ã�⸦ �õ��Ѵ�.		
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(pController, pTarget->GetActorLocation());

		// ���� ��������� ��ġ(�ֱ� �̵� ������) �� �����忡 ����صд�.
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(m_RecentTargetPos.SelectedKeyName, pTarget->GetActorLocation());
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}
}