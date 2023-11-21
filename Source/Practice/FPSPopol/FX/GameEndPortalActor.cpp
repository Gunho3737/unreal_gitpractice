// Fill out your copyright notice in the Description page of Project Settings.


#include "GameEndPortalActor.h"
#include "../Player/FPSPlayer.h"

// Sets default values
AGameEndPortalActor::AGameEndPortalActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	m_PSC = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));

	//Box°¡ root, ¹Ú½º¿¡ ºÎÂøµÊ
	SetRootComponent(m_Box);
	m_PSC->SetupAttachment(m_Box);

}

// Called when the game starts or when spawned
void AGameEndPortalActor::BeginPlay()
{
	Super::BeginPlay();
	
	m_Box->OnComponentBeginOverlap.AddDynamic(this, &AGameEndPortalActor::BeginOverlap);
	m_Box->OnComponentEndOverlap.AddDynamic(this, &AGameEndPortalActor::EndOverlap);
}

// Called every frame
void AGameEndPortalActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGameEndPortalActor::BeginOverlap(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom, int32 _Index, bool _bFromSweep, const FHitResult& _HitResult)
{
	AFPSPlayer* FPlayer = Cast<AFPSPlayer>(_OtherActor);

	if (IsValid(FPlayer))
	{
		LOG(Monster, Warning, TEXT("PlayerOvelLap to Teleporter"));
	}
}

void AGameEndPortalActor::EndOverlap(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom, int32 _Index)
{
}

