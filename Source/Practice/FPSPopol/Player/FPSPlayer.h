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
	//카메라컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UCameraComponent* m_Cam;
	//카메라암컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	USpringArmComponent* m_Arm;

	UPROPERTY(EditAnywhere, Category = "Input")
	TSubclassOf<ABullet> m_Bullet;

	class UFPS_MainWidget* CharHud;

	class UGameoverWidget* GameOverHUD;

	//발사애니메이션 체크, true면 애니메이션 실행중 아니면 실행아님
	bool ShootAnimationPlay;
	//재장전 애니메이션 체크, true면 애니메이션 실행중 아니면 실행아님
	bool ReloadAnimationPlay;

	//시퀀스 재생여부체크용 bool, true이면 현재 시퀀스 재생중 false이면 현재 시퀀스 재생중 아님
	bool SeqPlay;

	//잔탄 갯수
	int bullet;

	//최대 HP
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float MaxHP;

	//현재 HP
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float CurHP;

private:
	//매핑 컨텍스트
	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputMappingContext>	InputMapping;

	//인풋액션
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

	//현재 사망상태인지 아닌지 체크용 함수, true이면 사망상태
	bool DeathCheck();
	//현재 이동여부를 체크하는 함수
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
