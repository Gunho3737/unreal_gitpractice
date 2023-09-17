// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster_Base.h"
#include "AIController_Melee.h"
#include "../../Projectile/Projectile.h"

// Sets default values
AMonster_Base::AMonster_Base()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	////���� ��� - ���忡 ��ġ or ������ ��
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	////������ ��Ʈ�ѷ� UClass
	AIControllerClass = AAIController_Melee::StaticClass();

}

void AMonster_Base::OnConstruction(const FTransform& transform)
{
	FMonsterInfo* pInfo = nullptr;
	
	if (IsValid(m_MonTableRow.DataTable) && !m_MonTableRow.RowName.IsNone())
	{
		//�������Ʈ�� ������ ���������̺��� �� �̸��� �޾ƿ�
		pInfo = m_MonTableRow.DataTable->FindRow<FMonsterInfo>(m_MonTableRow.RowName, TEXT(""));
	
		// ������ m_Info �� ���� �־��ش�.
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

