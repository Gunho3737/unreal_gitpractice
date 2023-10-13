// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// SceneComponent 종류인 스피어 컴포넌트, 파티클 시스템 컴포넌트, 나이아가라 컴포넌트 생성 및 액터에 추가
	m_Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	m_PSC = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	m_NC = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));

	// 액터 컴포넌트인 투사체 무브 컴포넌트 추가
	m_ProjtileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));

	// SceneComponent 간의 계층관계구조 설정
	// 구 충돌체 컴포넌트가 최상위 루트, 그 밑에 자식으로 PSC, Niagara 추가
	SetRootComponent(m_Sphere);
	m_PSC->SetupAttachment(m_Sphere);
	m_NC->SetupAttachment(m_Sphere);
	m_Mesh->SetupAttachment(m_Sphere);

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

