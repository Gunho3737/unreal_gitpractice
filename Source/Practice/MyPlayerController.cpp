// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "Character/Monster/Monster_Base.h"
#include "Blueprint/Userwidget.h"

AMyPlayerController::AMyPlayerController()
{
	//마우스 커서 설정
	CurrentMouseCursor = EMouseCursor::Default;

	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

void AMyPlayerController::BeginPlay()
{
	//블루프린트 클래스를 불러와 커서를 세팅
	TSubclassOf<UUserWidget> pDefault = LoadClass<UUserWidget>(GetWorld(), TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/BPC_MouseBasicCursor.BPC_MouseBasicCursor_C'"));
	TSubclassOf<UUserWidget> pGrapHand = LoadClass<UUserWidget>(GetWorld(), TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/BPC_MouseGrabCursor.BPC_MouseGrabCursor_C'"));

	SetMouseCursorWidget(EMouseCursor::Default, CreateWidget(GetWorld(), pDefault));
	SetMouseCursorWidget(EMouseCursor::GrabHand, CreateWidget(GetWorld(), pGrapHand));
}


void AMyPlayerController::Tick(float _DT)
{
	Super::Tick(_DT);

	return;

	//최적화 문제로 틱마다 컨트롤러에서 충돌체크는 잘 안하려고함
	//객체 블루프린트 자체에서 커서모양을 바꾸는 방법을 사용 하는 중

	// 플레이어 컨트롤러에서 매 틱마다 마우스 위치로 RayCasting 시도
	// TraceChannel 은 PlayerAttack 채널 사용
	FHitResult result = {};
	bool bHit = GetHitResultUnderCursor(ECC_GameTraceChannel3, false, result);
	
	// 마우스 방향 Ray Check 에 걸린 대상이 있다면
	if (bHit)
	{
		// 걸린 대상이 몬스터 타입이면
		if (Cast<AMonster_Base>(result.GetActor()))
		{
			// 현재 마우스 상태를 GrabHand 로 변경
			CurrentMouseCursor = EMouseCursor::GrabHand;
		}
		else
		{
			CurrentMouseCursor = EMouseCursor::Default;
		}
	}
	else
	{
		// 충돌 중인 오브젝트가 없다면 항상 Default 상태로 둠
		CurrentMouseCursor = EMouseCursor::Default;
	}
}

