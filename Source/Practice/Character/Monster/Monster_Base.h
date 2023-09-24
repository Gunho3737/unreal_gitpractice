// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../../Header/GlobalHeader.h"
#include "behaviortree/BehaviorTree.h"
#include "behaviortree/blackboarddata.h"


#include "Monster_Base.generated.h"

UCLASS()
class PRACTICE_API AMonster_Base : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonster_Base();

private:
	//������ ������ ��� ����ü
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info", meta = (AllowPrivateAccess = "true"))
	FMonsterInfo			m_Info;

	//�������Ÿ������� ���� ���� Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info", meta = (AllowPrivateAccess = "true"))
	EMON_TYPE				m_MonType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info", meta = (AllowPrivateAccess = "true"))
	EMON_STATE				m_State;
	
	//���ͷ� MonsterInfo�� �������Ʈ���� ���� �ֵ��� ��
	//������ ���̺��� ��������� �޾ƿ� �������Ʈ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info", meta = (RowType = "MonsterInfo", AllowPrivateAccess = "true"))
	FDataTableRowHandle		m_MonTableRow;

	//���� ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info", meta = (RowType = "MonsterInfo", AllowPrivateAccess = "true"))
	class UWidgetComponent* m_WidgetComponent;

protected:
	// ����� �ൿƮ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* m_BehaviorTree;
	
	// ����� ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBlackboardData* m_Blackboard;

public:
	UBehaviorTree* GetBehaviorTree() { return m_BehaviorTree; }
	UBlackboardData* GetBloackboard() { return m_Blackboard; }
	const FMonsterInfo& GetMonsterInfo() { return m_Info; }

	EMON_STATE GetState() { return m_State; }
	void ChangeState(EMON_STATE _State) { m_State = _State; }


protected:
	// ������ �󿡼� �Ӽ�, ��ġ���� ����� �� ȣ��Ǵ� �Լ�
	virtual void OnConstruction(const FTransform& transform) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// �浹 ���� Delegate
private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom
		, FVector  _vNormalImpulse, const FHitResult& _Hit);

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom
		, int32 _Index, bool _bFromSweep, const FHitResult& _HitResult);

	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom
		, int32 _Index);

};
