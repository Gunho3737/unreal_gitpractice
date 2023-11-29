// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "../../Header/GlobalHeader.h"
#include "../../Projectile/Bullet.h"

#include "InputMappingContext.h"
#include "GameFramework/Character.h"
#include "FPSPlayer.generated.h"

UCLASS()
class PRACTICE_API AFPSPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	//ī�޶�������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UCameraComponent* m_Cam;
	//ī�޶��������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	USpringArmComponent* m_Arm;

	UPROPERTY(EditAnywhere, Category = "Input")
	TSubclassOf<ABullet> m_Bullet;

	class UFPS_MainWidget* CharHud;

	class UGameoverWidget* GameOverHUD;

	//�߻�ִϸ��̼� üũ, true�� �ִϸ��̼� ������ �ƴϸ� ����ƴ�
	bool ShootAnimationPlay;
	//������ �ִϸ��̼� üũ, true�� �ִϸ��̼� ������ �ƴϸ� ����ƴ�
	bool ReloadAnimationPlay;

	//������ �������üũ�� bool, true�̸� ���� ������ ����� false�̸� ���� ������ ����� �ƴ�
	bool SeqPlay;

	//��ź ����
	int bullet;

	//�ִ� HP
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float MaxHP;

	//���� HP
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float CurHP;

private:
	//���� ���ؽ�Ʈ
	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputMappingContext>	InputMapping;

	//��ǲ�׼�
	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputAction>			MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputAction>			RotationAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputAction>			JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputAction>			AttackAction;

	UPROPERTY(EditAnywhere, Category = "Animation")
	TSoftObjectPtr<UAnimMontage>			AttackMontage;

public:
	// Sets default values for this character's properties
	AFPSPlayer();
	~AFPSPlayer();

public:
	void Move(const FInputActionInstance& _Instance);
	void Rotation(const FInputActionInstance& _Instance);
	void Jump(const FInputActionInstance& _Instance);
	void Attack(const FInputActionInstance& _Instance);

	void BulletReload();
	void HPChange(float _DMG);

	//���� ����������� �ƴ��� üũ�� �Լ�, true�̸� �������
	bool DeathCheck();
	//���� �̵����θ� üũ�ϴ� �Լ�
	bool MovementStopCheck();

	void SetSeqPlay(bool _play);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
