// Fill out your copyright notice in the Description page of Project Settings.


#include "Effect_Base.h"

// Sets default values
AEffect_Base::AEffect_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//컴포넌트 세팅
	m_Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(m_Root);

	m_PSC = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
	m_PSC->SetupAttachment(m_Root);

	m_NC = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	m_NC->SetupAttachment(m_Root);

	//데이터 에셋 참조
	ConstructorHelpers::FObjectFinder<UEffectDataAsset> effectsetting(TEXT("/Script/Practice.EffectDataAsset'/Game/MyCharacter/Effect/DA_Effect.DA_Effect'"));
	if (effectsetting.Succeeded())
	{
		EffectSetting = effectsetting.Object;
	}

}

// Called when the game starts or when spawned
void AEffect_Base::BeginPlay()
{
	Super::BeginPlay();

	UEffectDataAsset* DataAsset = EffectSetting.LoadSynchronous();

	if (IsValid(DataAsset))
	{
		for (int32 i = 0; i < DataAsset->EffectDataArr.Num(); ++i)
		{
			if (Type == DataAsset->EffectDataArr[i].Type)
			{
				if (!DataAsset->EffectDataArr[i].Particle.IsNull())
				{
					UParticleSystem* Particle = DataAsset->EffectDataArr[i].Particle.LoadSynchronous();

					m_PSC->SetTemplate(Particle);
					m_PSC->OnSystemFinished.AddDynamic(this, &AEffect_Base::OnFinished);
				}

				if (!DataAsset->EffectDataArr[i].Niagara.IsNull())
				{
					UNiagaraSystem* pNiagaraSystem = DataAsset->EffectDataArr[i].Niagara.LoadSynchronous();
					m_NC->SetAsset(pNiagaraSystem);
				}
				return;
			}
		}
	}

	//데이처 에셋 세팅이 안되었을경우 파괴
	Destroy();
}

// Called every frame
void AEffect_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 나이아가라 컴포넌트가 재생중인 에셋(나이아가라 시스템) 이 있고, 재생이 완료되었다면
	if (m_NC->GetAsset() && m_NC->IsComplete())
	{
		Destroy();
	}

}

void AEffect_Base::OnFinished(UParticleSystemComponent* _PSC)
{
	UE_LOG(LogTemp, Warning, TEXT("ParticleSystem Finished"));
	Destroy();
}

