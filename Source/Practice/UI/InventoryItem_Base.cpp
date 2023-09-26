// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItem_Base.h"

#include "../Header/GlobalHeader.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"


void UInventoryItem_Base::InitFromData(UObject* _Data)
{
}

void UInventoryItem_Base::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInventoryItem_Base::NativeTick(const FGeometry& _geo, float _DT)
{
	Super::NativeTick(_geo, _DT);
}

