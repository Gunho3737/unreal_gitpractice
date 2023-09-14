// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordBeam.h"

ASwordBeam::ASwordBeam()
{
}

void ASwordBeam::BeginPlay()
{
	Super::BeginPlay();
	//UEffectManager::GetInst()->CreateEffect(GetWorld(), EEFFECT_TYPE::EXPLODE, GetLevel(), GetActorLocation());
}

void ASwordBeam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
