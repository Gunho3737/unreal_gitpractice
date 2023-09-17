// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster_Base.h"
#include "AIController_Melee.h"
#include "../../Projectile/Projectile.h"

// Sets default values
AMonster_Base::AMonster_Base()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	////빙의 방식 - 월드에 배치 or 스폰될 때
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	////빙의할 컨트롤러 UClass
	AIControllerClass = AAIController_Melee::StaticClass();

}

void AMonster_Base::OnConstruction(const FTransform& transform)
{
	FMonsterInfo* pInfo = nullptr;
	
	if (IsValid(m_MonTableRow.DataTable) && !m_MonTableRow.RowName.IsNone())
	{
		//블루프린트로 세팅한 데이터테이블의 행 이름을 받아옴
		pInfo = m_MonTableRow.DataTable->FindRow<FMonsterInfo>(m_MonTableRow.RowName, TEXT(""));
	
		// 몬스터의 m_Info 에 값을 넣어준다.
		if (nullptr != pInfo)
			m_Info = *pInfo;
	}
}

// Called when the game starts or when spawned
void AMonster_Base::BeginPlay()
{
	Super::BeginPlay();
	
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AMonster_Base::OnHit);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMonster_Base::BeginOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AMonster_Base::EndOverlap);

}

// Called every frame
void AMonster_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMonster_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMonster_Base::OnHit(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom, FVector _vNormalImpulse, const FHitResult& _Hit)
{
}

void AMonster_Base::BeginOverlap(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom, int32 _Index, bool _bFromSweep, const FHitResult& _HitResult)
{
}

void AMonster_Base::EndOverlap(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom, int32 _Index)
{
}

