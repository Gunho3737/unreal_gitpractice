// Fill out your copyright notice in the Description page of Project Settings.


#include "BTSDetectPlayer.h"
#include "AIController.h"
#include "behaviortree/BlackboardComponent.h"
#include "../Monster_Base.h"

UBTSDetectPlayer::UBTSDetectPlayer()
{
	// ���� ����
	NodeName = TEXT("Detect Player");

	// ���� ȣ�� ����
	Interval = 0.5f;
}

UBTSDetectPlayer::~UBTSDetectPlayer()
{
}

void UBTSDetectPlayer::TickNode(UBehaviorTreeComponent& _OwnCom, uint8* _NodeMemory, float _DT)
{
	Super::TickNode(_OwnCom, _NodeMemory, _DT);

	// ������ ���Ϳ����� ������ ��´�.
	AAIController* Controller = _OwnCom.GetAIOwner();
	if (!IsValid(Controller))
		return;

	AMonster_Base* pMonster = Cast<AMonster_Base>(Controller->GetPawn());
	if (!IsValid(pMonster))
		return;

	// ������ ������ Ž������ ��ġ�� �����´�.
	// Ž������ ���� �÷��̾ �ִ��� Ȯ���Ѵ�.	
	ACharacter* pPlayer = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	float Distance = FVector::Distance(pMonster->GetActorLocation(), pPlayer->GetActorLocation());


	bool bDetect = false;
	// Ž������ ���� �÷��̰� �־���.
	if (Distance < pMonster->GetMonsterInfo().DetectRange)
	{
		// �÷��̾ Ȯ�εǾ����� Ÿ��(�÷��̾�)�� �����忡 ����Ѵ�.
		Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), pPlayer);
		bDetect = true;
	}

	// Ž������ ���� �÷��̾ ������.
	else
	{
		Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), nullptr);
	}

#ifdef ENABLE_DRAW_DEBUG
	FColor color;
	bDetect ? color = FColor::Red : color = FColor::Green;
	DrawDebugSphere(GetWorld(), pMonster->GetActorLocation(), pMonster->GetMonsterInfo().DetectRange, 40, color, false, 0.4f);
#endif

}