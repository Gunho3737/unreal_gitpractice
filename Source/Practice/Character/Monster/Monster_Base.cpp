// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster_Base.h"
#include "Melee_Monster/AIController_Melee.h"
#include "Range_Monster/AIController_Range.h"
#include "../../Projectile/Bullet.h"
#include "Components/WidgetComponent.h"
#include "../../UI/Monster_InfoWidget.h"

// Sets default values
AMonster_Base::AMonster_Base()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//���� ��� - ���忡 ��ġ or ������ ��
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	//������ ��Ʈ�ѷ� UClass
	AIControllerClass = AAIController_Melee::StaticClass();



	//������ ĸ���� ����
	m_WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	m_WidgetComponent->SetupAttachment(GetCapsuleComponent());

}

void AMonster_Base::GetDamage(float _DMG)
{
	m_Info.CurHP -= _DMG;
	pAIController->GetBlackboardComponent()->SetValueAsFloat(FName("CurHP"), m_Info.CurHP);
}

void AMonster_Base::OffMonUI()
{
	pMonInfoWidget->SetMonUIVisibilty(ESlateVisibility::Hidden);
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

	switch (m_MonType)
	{
	case EMON_TYPE::MELEE:
		AIControllerClass = AAIController_Melee::StaticClass();
		break;
	case EMON_TYPE::RANGE:
		AIControllerClass = AAIController_Range::StaticClass();
		break;
	case EMON_TYPE::BOSS:
		break;
	default:
		break;
	}


}

// Called when the game starts or when spawned
void AMonster_Base::BeginPlay()
{
	Super::BeginPlay();
	
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AMonster_Base::OnHit);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMonster_Base::BeginOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AMonster_Base::EndOverlap);

	pAIController = Cast<AAIController>(GetController());
	if (IsValid(pAIController))
	{
		pAIController->GetBlackboardComponent()->SetValueAsVector(FName("SpawnPosition"), GetActorLocation());
		pAIController->GetBlackboardComponent()->SetValueAsFloat(FName("AttackRange"), m_Info.AttackRange);
		pAIController->GetBlackboardComponent()->SetValueAsFloat(FName("DetectRange"), m_Info.DetectRange);
		pAIController->GetBlackboardComponent()->SetValueAsFloat(FName("MaxHP"), m_Info.MaxHP);
		pAIController->GetBlackboardComponent()->SetValueAsFloat(FName("CurHP"), m_Info.CurHP);
		pAIController->GetBlackboardComponent()->SetValueAsBool(FName("IsAttackAnimationPlay"), false);
	}

	pMonInfoWidget = Cast<UMonster_InfoWidget>((m_WidgetComponent->GetWidget()));

	if (!IsValid(pMonInfoWidget))
	{
	//	UE_LOG(LogTemp, Warning, TEXT("���� ������ �ȵƽ��ϴ�"));
	}
	else
	{
		switch (m_MonType)
		{
		case EMON_TYPE::MELEE:
			pMonInfoWidget->SetTextBlock("MeleeMonster");
			break;
		case EMON_TYPE::RANGE:
			pMonInfoWidget->SetTextBlock("RangeMonster");
			break;
		case EMON_TYPE::BOSS:
			break;
		default:
			break;
		}
		pMonInfoWidget->SetHPRatio(1.f);
	}


}

// Called every frame
void AMonster_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//static float fIntence = 0.0f;
	//fIntence += DeltaTime * 0.1f;
	////����ȭ ��Ų Scalar �� �̸��� "Burn Intence"�� ��� Scalar�� ���� �����Ѵ�
	//GetMesh()->SetScalarParameterValueOnMaterials(TEXT("Burn Intence"), fIntence);
	float MaxHP = pAIController->GetBlackboardComponent()->GetValueAsFloat(FName("MaxHP"));
	float CurHP = pAIController->GetBlackboardComponent()->GetValueAsFloat(FName("CurHP"));
	float Ratio = CurHP / MaxHP;

	pMonInfoWidget->SetHPRatio(Ratio);

	//���������� �����Ų ���͸� ����, ���� �������� �ƴ� ���� ��ġ�������� �̵�
	pAIController->GetBlackboardComponent()->SetValueAsVector(FName("SpawnPosition"), GetActorLocation());

	UObject* player = pAIController->GetBlackboardComponent()->GetValueAsObject(FName("Target"));

	//�÷��̾� Ž���� ������ ��� ���� UI ����
	if (player == nullptr)
	{
		OffMonUI();
	}
	else
	{
		pMonInfoWidget->SetMonUIVisibilty(ESlateVisibility::Visible);
	}

	if (m_State == EMON_STATE::DEAD)
	{
		OffMonUI();
	}
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
	ABullet* pAB = Cast<ABullet>(_OtherActor);

	if (IsValid(pAB))
	{
	//	LOG(LogTemp, Warning, TEXT("BulletOverLap To Monster"));
		//GetDamage(100.f);
		if (m_State != EMON_STATE::DEAD)
		{
			GetDamage(200.f);
			pAB->BulletDeath();
		}
	}
	

}

void AMonster_Base::EndOverlap(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom, int32 _Index)
{
}

