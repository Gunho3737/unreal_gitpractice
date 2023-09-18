// Fill out your copyright notice in the Description page of Project Settings.


#include "BTSDetectPlayer.h"
#include "AIController.h"
#include "behaviortree/BlackboardComponent.h"
#include "../Monster_Base.h"

UBTSDetectPlayer::UBTSDetectPlayer()
{
	// 서비스 설명
	NodeName = TEXT("Detect Player");

	// 서비스 호출 간격
	Interval = 0.5f;
}

UBTSDetectPlayer::~UBTSDetectPlayer()
{
}

void UBTSDetectPlayer::TickNode(UBehaviorTreeComponent& _OwnCom, uint8* _NodeMemory, float _DT)
{
	Super::TickNode(_OwnCom, _NodeMemory, _DT);

	// 빙의한 몬스터에대한 참조를 얻는다.
	AAIController* Controller = _OwnCom.GetAIOwner();
	if (!IsValid(Controller))
		return;

	AMonster_Base* pMonster = Cast<AMonster_Base>(Controller->GetPawn());
	if (!IsValid(pMonster))
		return;

	// 빙의한 몬스터의 탐지범위 수치를 가져온다.
	// 탐지범위 내에 플레이어가 있는지 확인한다.	
	ACharacter* pPlayer = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	float Distance = FVector::Distance(pMonster->GetActorLocation(), pPlayer->GetActorLocation());


	bool bDetect = false;
	// 탐지범위 내에 플레이가 있었다.
	if (Distance < pMonster->GetMonsterInfo().DetectRange)
	{
		// 플레이어가 확인되었으면 타겟(플레이어)을 블랙보드에 기록한다.
		Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), pPlayer);
		bDetect = true;
	}

	// 탐지범위 내에 플레이어가 없었다.
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