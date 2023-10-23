// Fill out your copyright notice in the Description page of Project Settings.


#include "Character2D_Base.h"

//플립북 컴포넌트
#include "PaperFlipbookComponent.h"

bool ACharacter2D_Base::ChangeState(EPLAYER2D_STATE _NextState)
{
	//현재스테이트와 다음 스테이트가 같으면 아무것도 안하고 리턴
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

	//현재 상태에 맞춘 플립북을 재생
	PlayFlipbook(CurState, CurDir);

	return false;
}

void ACharacter2D_Base::PlayFlipbook(EPLAYER2D_STATE _CurState, EPLAYER2D_DIR _CurDir, bool _bLoop, int32 _StartFrame)
{
	//Array전체를 돌면서
	for (int32 i = 0; i < FlipbookInfoArray.Num(); ++i)
	{
		//내 현재 state와 현재 dir와 같은 세팅을 가진 flipbook을 찾았을시
		if (_CurState == FlipbookInfoArray[i].State && _CurDir == FlipbookInfoArray[i].Dir)
		{
			//그 Array에 플립북 정보가 들어가 있으면
			if (IsValid(FlipbookInfoArray[i].Flipbook))
			{
				//스프라이트를 찾아낸 플립북으로 세팅하고
				GetSprite()->SetFlipbook(FlipbookInfoArray[i].Flipbook);
				//x번째 프레임부터 재생하며
				GetSprite()->SetPlaybackPositionInFrames(_StartFrame, false);
				//루프 여부를 세팅한다음
				GetSprite()->SetLooping(_bLoop);
				//플립북을 재생
				GetSprite()->Play();
			}

			return;
		}
	}
}

void ACharacter2D_Base::BeginPlay()
{
	Super::BeginPlay();

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
}

ACharacter2D_Base::ACharacter2D_Base()
	: CurState(EPLAYER2D_STATE::NONE), CurDir(EPLAYER2D_DIR::RIGHT)
{
	//카메라 컴포넌트를 Root에 부착
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(GetRootComponent());
}

ACharacter2D_Base::~ACharacter2D_Base()
{
}
