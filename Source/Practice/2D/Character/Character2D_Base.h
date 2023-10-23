// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "PaperFlipbook.h"
#include "../../Header/GlobalHeader.h"

#include "Character2D_Base.generated.h"

/**
 * 
 */

//2D캐릭터의 상태를 나타냄
UENUM(BlueprintType)
enum class EPLAYER2D_STATE : uint8
{
	IDLE,
	MOVE,
	JUMP,
	ATTACK,
	FALLDOWN,
	GETDAMAGE,
	DEAD,
	NONE,
};

UENUM(BlueprintType)
enum class EPLAYER2D_DIR : uint8
{
	LEFT,
	RIGHT,
};

//array안에 들어갈 flipbook들의 정보가 담긴 구조체
USTRUCT(Atomic, BlueprintType)
struct FFlipbookInfo
{
	GENERATED_BODY()

public:
	//무슨 스테이트 상에서 실행될 것인지
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EPLAYER2D_STATE		State;
	//플레이어의 방향이 좌방향인지 우방향 인지
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EPLAYER2D_DIR		Dir;  

	//플레이어의 State,Dir 이 겹쳣을때 실행시킬 FlipBookComponent
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbook* Flipbook;
};

UCLASS()
class PRACTICE_API ACharacter2D_Base : public APaperCharacter
{
	GENERATED_BODY()

public:
	//캐릭터가 사용할 플립북을 모아둘 TArray
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, meta = (AllowPrivateAccess = "true"))
	TArray<FFlipbookInfo> FlipbookInfoArray;
	
	//플레이어의 현재 방향
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, meta = (AllowPrivateAccess = "true"))
	EPLAYER2D_DIR CurDir;
	
	//플레이어의 현재 상태
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, meta = (AllowPrivateAccess = "true"))
	EPLAYER2D_STATE			CurState;

	//카메라 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Component, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

public:
	UCameraComponent* GetCamera() { return Camera; }

	//현재 상태를 전환하기 위한 함수
	bool ChangeState(EPLAYER2D_STATE _NextState);
	
	//상태와 방향을 넣어주면, 그거에 맞춘 플립북을 재생하는 함수
	void PlayFlipbook(EPLAYER2D_STATE _CurState, EPLAYER2D_DIR _CurDir, bool _bLoop = true, int32 _StartFrame = 0);

public:

	virtual void BeginPlay() override;
	virtual void Tick(float _DT) override;
	//인풋 바인딩을 위한 함수
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	ACharacter2D_Base();
	virtual ~ACharacter2D_Base();
};
