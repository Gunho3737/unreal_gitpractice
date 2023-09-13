// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character_Base.h"
#include "../Header/GlobalHeader.h"

#include "Animation/AnimInstance.h"
#include "Character_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API UCharacter_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	//ĳ������ �����Ʈ ������ �������� ���� Acharcters
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "멤버변수")
	ACharacter_Base* Character;

	//���ӵ��� ���� �̵� ������ �޾ƿ��� ���� �ʿ��� �����Ʈ
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "컴포넌트")
	UCharacterMovementComponent* Movement;

	//���� �ӵ�
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "데이터")
	FVector		LocalVelocity;

	//�ӷ�
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "데이터")
	float		MoveSpeed;

	//���� �̵����θ� üũ�ϴ� bool��
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "데이터")
	bool		IsMove;

	//���� �߶���θ� üũ�ϴ� bool��
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "데이터")
	bool		IsFall;

	//현재 공격여부를 체크하는 bool값
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "데이터")
	bool IsAttack;

	//현재 애니메이션이 재생중인지 체크하는 bool값
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "데이터")
	bool IsAttackAnimPlay;
	

	//공격모션 몽타쥬를 위한 가중치 float
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "데이터")
	float AttackWeight;

	//카메라가 바라보고 있는 방향벡터 LookAt값
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "데이터")
	FVector CameraLookAt;
public:
	// �ʱ�ȭ
	virtual void NativeInitializeAnimation() override;

	// ���忡 ���� ������ ȣ��
	virtual void NativeBeginPlay() override;

	// �� ƽ(������) ���� ȣ��
	virtual void NativeUpdateAnimation(float _fDeltaTime) override;

public:
	//노티파이 바인드 함수
	//UFUNCTION() 붙혀야함
	UFUNCTION()
	void AnimNotify_AttStart();

	UFUNCTION()
	void AnimNotify_AttComboCheck();

	UFUNCTION()
	void AnimNotify_AttEnd();

	UFUNCTION()
	void AnimNotify_ComboStart();

	UFUNCTION()
	void AnimNotify_ComboEnd();

};
