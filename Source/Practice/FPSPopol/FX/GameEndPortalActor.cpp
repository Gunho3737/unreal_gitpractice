// Fill out your copyright notice in the Description page of Project Settings.


#include "GameEndPortalActor.h"

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
	
}

// Called every frame
void AGameEndPortalActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

