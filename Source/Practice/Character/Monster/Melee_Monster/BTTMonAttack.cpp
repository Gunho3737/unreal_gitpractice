// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTMonAttack.h"
#include "../Monster_Base.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "../../../FPSPopol/Player/FPSPlayer.h"

UBTTMonAttack::UBTTMonAttack()
{
}

EBTNodeResult::Type UBTTMonAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AMonster_Base* pMonster = Cast<AMonster_Base>(OwnerComp.GetAIOwner()->GetPawn());

	if (IsValid(pMonster) == false)
	{
		//���ʰ� ������ ����
		return EBTNodeResult::Failed;
	}

	if (true == OwnerComp.GetBlackboardComponent()->GetValueAsBool(FName("IsAttackAnimationPlay")))
	{
		//�ִϸ��̼��� �̹� �������̸� �۾����������� �ٸ����� �Ѿ�� �ȵǹǷ� succeeded�� �Ѱ���
		return EBTNodeResult::Succeeded;
	}

	//���͸� �÷��̾� �������� ȸ����Ű��
	UObject* pObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("TraceTarget"));
	if (IsValid(pObject))
	{
		AActor* pTarget = Cast<AActor>(pObject);
		FVector PlayerPos = pTarget->GetActorLocation();
		//�÷��̾� ��ġ�� ȸ��
		//���� ���� �ȵǴ��� �ٸ��� ����
		pMonster->GetActorRotation().RotateVector(PlayerPos);
	}

	
	float Speed = pMonster->GetMovementComponent()->Velocity.Size();

	if (Speed >= 0.f)
	{
		//VeloCity������Ű��
		pMonster->GetMovementComponent()->Velocity = { 0.f,0.f,0.f };
	}

	switch (pMonster->GetMonsterType())
	{
	case EMON_TYPE::MELEE:
		{
			pMonster->ChangeState(EMON_STATE::MELEE_ATTACK);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(FName("IsAttackAnimationPlay"), true);
		}
		break;
	case EMON_TYPE::RANGE:
		{
			pMonster->ChangeState(EMON_STATE::RANGE_ATTACK);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(FName("IsAttackAnimationPlay"), true);
		}
		break;
	case EMON_TYPE::BOSS:
		{
			pMonster->ChangeState(EMON_STATE::MELEE_ATTACK);
		}
		break;
	default:
		break;
	}

	return EBTNodeResult::Succeeded;
}
