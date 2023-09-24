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
	//몬스터의 정보가 담긴 구조체
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info", meta = (AllowPrivateAccess = "true"))
	FMonsterInfo			m_Info;

	//근접원거리보스와 같은 몬스터 타입
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info", meta = (AllowPrivateAccess = "true"))
	EMON_TYPE				m_MonType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info", meta = (AllowPrivateAccess = "true"))
	EMON_STATE				m_State;
	
	//필터로 MonsterInfo만 블루프린트에서 볼수 있도록 함
	//데이터 테이블을 멤버변수로 받아와 블루프린트에서 세팅
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info", meta = (RowType = "MonsterInfo", AllowPrivateAccess = "true"))
	FDataTableRowHandle		m_MonTableRow;

	//위젯 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info", meta = (RowType = "MonsterInfo", AllowPrivateAccess = "true"))
	class UWidgetComponent* m_WidgetComponent;

protected:
	// 사용할 행동트리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* m_BehaviorTree;
	
	// 사용할 블랙보드
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBlackboardData* m_Blackboard;

public:
	UBehaviorTree* GetBehaviorTree() { return m_BehaviorTree; }
	UBlackboardData* GetBloackboard() { return m_Blackboard; }
	const FMonsterInfo& GetMonsterInfo() { return m_Info; }

	EMON_STATE GetState() { return m_State; }
	void ChangeState(EMON_STATE _State) { m_State = _State; }


protected:
	// 에디터 상에서 속성, 위치값이 변경될 때 호출되는 함수
	virtual void OnConstruction(const FTransform& transform) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// 충돌 관련 Delegate
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
