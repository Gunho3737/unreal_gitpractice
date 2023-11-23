// Fill out your copyright notice in the Description page of Project Settings.

#include "StartLevelGameMode.h"
#include "Blueprint/UserWidget.h"
#include "UI/StartMenuWidget.h"

AStartLevelGameMode::AStartLevelGameMode()
{
	//UI�� ���� �������Ʈ �ε��ؿ�
	ConstructorHelpers::FClassFinder<UUserWidget> ManHUD(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/MyCharacter/StartLevel/StartLevelUI/BPC_StartLevelWidget.BPC_StartLevelWidget_C'"));

	if (ManHUD.Succeeded())
	{
		m_MainHudClass = ManHUD.Class;
	}
}

AStartLevelGameMode::~AStartLevelGameMode()
{
}

void AStartLevelGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(m_MainHudClass))
	{
		m_MainHUD = Cast<UStartMenuWidget>(CreateWidget(GetWorld(), m_MainHudClass));
		if (!IsValid(m_MainHUD))
		{
			// �ٿ�ĳ���� ���� ==> UMainHUD_Base �κ��� �Ļ��� �������Ʈ�� �ƴϴ�.

		}
		else
		{
			//����Ʈ�� ���� �߰�
			m_MainHUD->AddToViewport();
		}
	}

	APlayerController* pController = GetWorld()->GetFirstPlayerController();

	FInputModeUIOnly uionly{};
	pController->SetInputMode(uionly);
	pController->bShowMouseCursor = true;
}
