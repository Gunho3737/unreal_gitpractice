// Fill out your copyright notice in the Description page of Project Settings.


#include "GameEndPortalActor.h"
#include "../Player/FPSPlayer.h"
#include "../FPSPlayLevelGamemode.h"

// Sets default values
AGameEndPortalActor::AGameEndPortalActor()
	: ClearFadeOn(false), Fadeout(0.0f)
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

	if (ClearFadeOn == true)
	{
		AFPSPlayLevelGamemode* GameMode = Cast<AFPSPlayLevelGamemode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (IsValid(GameMode))
		{
			float DT = DeltaTime * 0.5f;
			Fadeout += DT;
			GameMode->GetGameOverHUD()->SetClearFadeout(Fadeout);
		}
	}

}

void AGameEndPortalActor::BeginOverlap(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom, int32 _Index, bool _bFromSweep, const FHitResult& _HitResult)
{
	AFPSPlayer* FPlayer = Cast<AFPSPlayer>(_OtherActor);

	if (IsValid(FPlayer))
	{
		LOG(Monster, Warning, TEXT("PlayerOvelLap to Teleporter"));

		ClearFadeOn = true;

		AFPSPlayLevelGamemode* GameMode = Cast<AFPSPlayLevelGamemode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (IsValid(GameMode))
		{
			GameMode->GetMainHUD()->SetVisibility(ESlateVisibility::Hidden);
			GameMode->GetGameOverHUD()->SetVisibility(ESlateVisibility::Visible);
			//GameMode->GetGameOverHUD()->SetClearFadeout(1.0f);
		}
	}
}

void AGameEndPortalActor::EndOverlap(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom, int32 _Index)
{
}

