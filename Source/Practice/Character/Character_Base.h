// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "EngineMinimal.h"

#include "InputMappingContext.h"

#include "../Header/GlobalHeader.h"
#include "../System/IA_DataAsset.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "../Projectile/SwordBeam.h"
#include "../Effect/Decal/FootPrintDecal.h"

#include "Character_Base.generated.h"


UCLASS()
class PRACTICE_API ACharacter_Base : public ACharacter
{
	GENERATED_BODY()

public:
	//EngineMinimal.h include �ʿ�
	//ī�޶� ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UCameraComponent* m_Cam;

	//�� ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	USpringArmComponent* m_Arm;


private:

	//매핑 컨텍스트
	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputMappingContext>	InputMapping;

	//매핑 컨테스트세팅을 받아오기 위한 DataAsset
	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UIA_DataAsset>			InputActionSetting;

	//인풋액션
	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputAction>			MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputAction>			RotationAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputAction>			JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputAction>			SprintToggleAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputAction>			AttackAction;

	UPROPERTY(EditAnywhere, Category = "Animation")
	TSoftObjectPtr<UAnimMontage>			AttackMontage;
	
public:
	//현재 캐릭터가 공격을 하고 있는가
	bool IsAttack;

	//현재 캐릭터가 콤보 공격을하는가
	bool IsCombo;

	//사용할 소드빔 포인터
	UPROPERTY(EditAnywhere, Category = "Input")
	TSubclassOf<ASwordBeam> m_SwordBeam;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	TSubclassOf<AFootPrintDecal> FootPrintDecal_L;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	TSubclassOf<AFootPrintDecal> FootPrintDecal_R;

public:
	// Sets default values for this character's properties
	ACharacter_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	TSoftObjectPtr<UAnimMontage> GetAttackMontage() { return AttackMontage; }
	UCameraComponent* GetCamera() { return m_Cam; }
	USpringArmComponent* GetArm() { return m_Arm; }
	void CreateFootPrint(FootPrint_Type _foottype);

private:
	void Move(const FInputActionInstance& _Instance);
	void Rotation(const FInputActionInstance& _Instance);
	void SprintToggle(const FInputActionInstance& _Instance);
	void Jump(const FInputActionInstance& _Instance);
	void Attack(const FInputActionInstance& _Instance);
	void SwordWave(const FInputActionInstance& _Instance);
	void OpenInventory(const FInputActionInstance& _Instance);

	// 충돌 관련 Delegate
private:
	//충돌시 호출되는 함수
	UFUNCTION()
	void OnHit(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom
		, FVector  _vNormalImpulse, const FHitResult& _Hit);
	//오버랩 시작시 호출되는 함수
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom
		, int32 _Index, bool _bFromSweep, const FHitResult& _HitResult);
	//오버랩 끝날시 호출 되는 함수
	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom
		, int32 _Index);

};
