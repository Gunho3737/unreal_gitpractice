// Fill out your copyright notice in the Description page of Project Settings.


#include "Character2D_Base.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "PaperFlipbookComponent.h"
#include "InputMappingContext.h"

ACharacter2D_Base::ACharacter2D_Base()
	: CurState(EPLAYER2D_STATE::NONE), CurDir(EPLAYER2D_DIR::RIGHT)
{
	//ī�޶� ������Ʈ�� Root�� ����
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(GetRootComponent());
}

ACharacter2D_Base::~ACharacter2D_Base()
{
}

void ACharacter2D_Base::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* pController = Cast<APlayerController>(GetController());

	if (pController)
	{
		ULocalPlayer* pLocalPlayer = pController->GetLocalPlayer();

		if (pLocalPlayer && !InputMapping.IsNull())
		{
			UEnhancedInputLocalPlayerSubsystem* pSubsystem = pLocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
			pSubsystem->AddMappingContext(InputMapping.LoadSynchronous(), 0);
		}
	}

	CurDir = EPLAYER2D_DIR::RIGHT;
	ChangeState(EPLAYER2D_STATE::IDLE);
}

void ACharacter2D_Base::Tick(float _DT)
{
	Super::Tick(_DT);
}

void ACharacter2D_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* InputCom = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (nullptr == InputCom)
		return;

	if (!MoveAction.IsNull())
	{
		InputCom->BindAction(MoveAction.LoadSynchronous(), ETriggerEvent::Triggered, this, &ACharacter2D_Base::MoveFunction);
	}

	if (!JumpAction.IsNull())
	{
		InputCom->BindAction(JumpAction.LoadSynchronous(), ETriggerEvent::Triggered, this, &ACharacter2D_Base::JumpFunction);
	}
}


bool ACharacter2D_Base::ChangeState(EPLAYER2D_STATE _NextState)
{
	//���罺����Ʈ�� ���� ������Ʈ�� ������ �ƹ��͵� ���ϰ� ����
	if (CurState == _NextState)
		return false;

	CurState = _NextState;

	switch (CurState)
	{
	case EPLAYER2D_STATE::IDLE:
		break;
	case EPLAYER2D_STATE::MOVE:
		break;
	case EPLAYER2D_STATE::JUMP:
		break;
	case EPLAYER2D_STATE::ATTACK:
		break;
	case EPLAYER2D_STATE::FALLDOWN:
		break;
	case EPLAYER2D_STATE::GETDAMAGE:
		break;
	case EPLAYER2D_STATE::DEAD:
		break;
	case EPLAYER2D_STATE::NONE:
		break;
	default:
		break;
	}

	//���� ���¿� ���� �ø����� ���
	PlayFlipbook(CurState, CurDir);

	return false;
}

void ACharacter2D_Base::PlayFlipbook(EPLAYER2D_STATE _CurState, EPLAYER2D_DIR _CurDir, bool _bLoop, int32 _StartFrame)
{
	//�ø����� �����Ű�� �Լ�

	//Array��ü�� ���鼭
	for (int32 i = 0; i < FlipbookInfoArray.Num(); ++i)
	{
		//�� ���� state�� ���� dir�� ���� ������ ���� flipbook�� ã������
		if (_CurState == FlipbookInfoArray[i].State && _CurDir == FlipbookInfoArray[i].Dir)
		{
			//�� Array�� �ø��� ������ �� ������
			if (IsValid(FlipbookInfoArray[i].Flipbook))
			{
				//��������Ʈ�� ã�Ƴ� �ø������� �����ϰ�
				GetSprite()->SetFlipbook(FlipbookInfoArray[i].Flipbook);
				//x��° �����Ӻ��� ����ϸ�
				GetSprite()->SetPlaybackPositionInFrames(_StartFrame, false);
				//���� ���θ� �����Ѵ���
				GetSprite()->SetLooping(_bLoop);
				//�ø����� ���
				GetSprite()->Play();
			}

			return;
		}
	}
}

void ACharacter2D_Base::MoveFunction(const FInputActionInstance& _Instance)
{
	LOG(Player, Warning, TEXT("2D Char MoveFunc"));
}

void ACharacter2D_Base::JumpFunction(const FInputActionInstance& _Instance)
{
	LOG(Player, Warning, TEXT("2D Char JumpFunc"));
	Jump();
}