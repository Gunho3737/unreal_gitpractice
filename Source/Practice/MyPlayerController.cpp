// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "Character/Monster/Monster_Base.h"
#include "Blueprint/Userwidget.h"

AMyPlayerController::AMyPlayerController()
{
	//���콺 Ŀ�� ����
	CurrentMouseCursor = EMouseCursor::Default;

	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

void AMyPlayerController::BeginPlay()
{
	//�������Ʈ Ŭ������ �ҷ��� Ŀ���� ����
	TSubclassOf<UUserWidget> pDefault = LoadClass<UUserWidget>(GetWorld(), TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/BPC_MouseBasicCursor.BPC_MouseBasicCursor_C'"));
	TSubclassOf<UUserWidget> pGrapHand = LoadClass<UUserWidget>(GetWorld(), TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/BPC_MouseGrabCursor.BPC_MouseGrabCursor_C'"));

	SetMouseCursorWidget(EMouseCursor::Default, CreateWidget(GetWorld(), pDefault));
	SetMouseCursorWidget(EMouseCursor::GrabHand, CreateWidget(GetWorld(), pGrapHand));
}


void AMyPlayerController::Tick(float _DT)
{
	Super::Tick(_DT);

	return;

	//����ȭ ������ ƽ���� ��Ʈ�ѷ����� �浹üũ�� �� ���Ϸ�����
	//��ü �������Ʈ ��ü���� Ŀ������� �ٲٴ� ����� ��� �ϴ� ��

	// �÷��̾� ��Ʈ�ѷ����� �� ƽ���� ���콺 ��ġ�� RayCasting �õ�
	// TraceChannel �� PlayerAttack ä�� ���
	FHitResult result = {};
	bool bHit = GetHitResultUnderCursor(ECC_GameTraceChannel3, false, result);
	
	// ���콺 ���� Ray Check �� �ɸ� ����� �ִٸ�
	if (bHit)
	{
		// �ɸ� ����� ���� Ÿ���̸�
		if (Cast<AMonster_Base>(result.GetActor()))
		{
			// ���� ���콺 ���¸� GrabHand �� ����
			CurrentMouseCursor = EMouseCursor::GrabHand;
		}
		else
		{
			CurrentMouseCursor = EMouseCursor::Default;
		}
	}
	else
	{
		// �浹 ���� ������Ʈ�� ���ٸ� �׻� Default ���·� ��
		CurrentMouseCursor = EMouseCursor::Default;
	}
}

