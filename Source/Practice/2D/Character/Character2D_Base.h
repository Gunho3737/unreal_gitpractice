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

//2Dĳ������ ���¸� ��Ÿ��
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

//array�ȿ� �� flipbook���� ������ ��� ����ü
USTRUCT(Atomic, BlueprintType)
struct FFlipbookInfo
{
	GENERATED_BODY()

public:
	//���� ������Ʈ �󿡼� ����� ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EPLAYER2D_STATE		State;
	//�÷��̾��� ������ �¹������� ����� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EPLAYER2D_DIR		Dir;  

	//�÷��̾��� State,Dir �� �㫉���� �����ų FlipBookComponent
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbook* Flipbook;
};

UCLASS()
class PRACTICE_API ACharacter2D_Base : public APaperCharacter
{
	GENERATED_BODY()

public:
	//ĳ���Ͱ� ����� �ø����� ��Ƶ� TArray
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, meta = (AllowPrivateAccess = "true"))
	TArray<FFlipbookInfo> FlipbookInfoArray;
	
	//�÷��̾��� ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, meta = (AllowPrivateAccess = "true"))
	EPLAYER2D_DIR CurDir;
	
	//�÷��̾��� ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, meta = (AllowPrivateAccess = "true"))
	EPLAYER2D_STATE			CurState;

	//ī�޶� ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Component, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

public:
	UCameraComponent* GetCamera() { return Camera; }

	//���� ���¸� ��ȯ�ϱ� ���� �Լ�
	bool ChangeState(EPLAYER2D_STATE _NextState);
	
	//���¿� ������ �־��ָ�, �װſ� ���� �ø����� ����ϴ� �Լ�
	void PlayFlipbook(EPLAYER2D_STATE _CurState, EPLAYER2D_DIR _CurDir, bool _bLoop = true, int32 _StartFrame = 0);

public:

	virtual void BeginPlay() override;
	virtual void Tick(float _DT) override;
	//��ǲ ���ε��� ���� �Լ�
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	ACharacter2D_Base();
	virtual ~ACharacter2D_Base();
};
