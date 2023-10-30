// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Header/GlobalHeader.h"
#include "FPSPlayer.h"
#include "Animation/AnimInstance.h"
#include "FPSPlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API UFPSPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	//�÷��̾��� ������ �������� �ִϸ��̼��� �����ϱ� ������ ������ �÷��̾ �����ͷ� ��� ����
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "member")
	AFPSPlayer* Character;

	//�÷��̾��� �����Ʈ
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Component")
	UCharacterMovementComponent* Movement;

	//�÷��̾��� �ӵ���
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Data")
	FVector		LocalVelocity;

	//ī�޶� �ٶ󺸰� �ִ� ���⺤�� LookAt��
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Data")
	FVector CameraLookAt;

	//�÷��̾��� �ӷ°�, �ӷ��� �ӵ��� �ٸ��� ������ ��������
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Data")
	float		MoveSpeed;

	//���� �̵������� üũ�� bool��
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Data")
	bool		IsMove;

	//���� ���ݿ��θ� üũ�ϴ� bool��
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "������")
	bool		IsAttack;

	//���ݸ�� ��Ÿ�긦 ���� ����ġ float
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "������")
	float	 AttackWeight;
public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeBeginPlay() override;

	virtual void NativeUpdateAnimation(float _fDeltaTime) override;

	UFUNCTION()
	void AnimNotify_ShootStart();

	UFUNCTION()
	void AnimNotify_ShootEnd();

	UFUNCTION()
	void AnimNotify_ReloadStart();

	UFUNCTION()
	void AnimNotify_ReloadEnd();
};
