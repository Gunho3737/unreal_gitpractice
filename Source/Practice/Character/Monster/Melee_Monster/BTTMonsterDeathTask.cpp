// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTMonsterDeathTask.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Monster_Base.h"
#include "AIController.h"

UBTTMonsterDeathTask::UBTTMonsterDeathTask()
	: time(0.0f)
{
	//�̰� �ѵ־� ƽ�׽�ũ �����
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTMonsterDeathTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);


	float curhp = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(TEXT("CurHP"));

	//����hp�� 0���ϸ� �������
	if (curhp < 0.0f)
	{
		AMonster_Base* pMonster = Cast<AMonster_Base>(OwnerComp.GetAIOwner()->GetPawn());

		if (IsValid(pMonster))
		{
			pMonster->ChangeState(EMON_STATE::DEAD);
			return EBTNodeResult::InProgress;
		}
	}

	return EBTNodeResult::Failed;
}

void UBTTMonsterDeathTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	LOG(Player, Warning, TEXT("Death TickTask On"));

	AMonster_Base* pMonster = Cast<AMonster_Base>(OwnerComp.GetAIOwner()->GetPawn());
	time += DeltaSeconds * 0.2f;
	//����ȭ ��Ų Scalar �� �̸��� "Burn Intence"�� ��� Scalar�� ���� �����Ѵ�
	pMonster->GetMesh()->SetScalarParameterValueOnMaterials(TEXT("Burn Intence"), time);

	if (time > 1.1f)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		pMonster->Destroy();
		return;
	}


}
