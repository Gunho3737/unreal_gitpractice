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
		//오너가 없으면 리턴
		return EBTNodeResult::Failed;
	}

	if (true == OwnerComp.GetBlackboardComponent()->GetValueAsBool(FName("IsAttackAnimationPlay")))
	{
		//애니메이션이 이미 실행중이면 작업생략하지만 다른노드로 넘어가면 안되므로 succeeded로 넘겨줌
		return EBTNodeResult::Succeeded;
	}

	//몬스터를 플레이어 방향으로 회전시키기
	UObject* pObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("TraceTarget"));
	if (IsValid(pObject))
	{
		AActor* pTarget = Cast<AActor>(pObject);
		FVector PlayerPos = pTarget->GetActorLocation();
		//플레이어 위치로 회전
		//지금 적용 안되는중 다른거 쓰기
		pMonster->GetActorRotation().RotateVector(PlayerPos);
	}

	
	float Speed = pMonster->GetMovementComponent()->Velocity.Size();

	if (Speed >= 0.f)
	{
		//VeloCity정지시키기
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
