// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSPlayLevelGamemode.h"

AFPSPlayLevelGamemode::AFPSPlayLevelGamemode()
{
	ConstructorHelpers::FClassFinder<APawn> Finder(TEXT("/Script/Engine.Blueprint'/Game/FPSPopol/Character/BPC_FPSPlayer.BPC_FPSPlayer_C'"));
	if (Finder.Succeeded())
	{
		DefaultPawnClass = Finder.Class;
	}
}

AFPSPlayLevelGamemode::~AFPSPlayLevelGamemode()
{
}

void AFPSPlayLevelGamemode::BeginPlay()
{
	Super::BeginPlay();
}
