// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory_Base.h"

#include "../Header/GlobalHeader.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"


void UInventory_Base::AddItem(UObject* _ItemData)
{
}

void UInventory_Base::Clear()
{
}

void UInventory_Base::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInventory_Base::NativeTick(const FGeometry& _geo, float _DT)
{
	Super::NativeTick(_geo, _DT);
}

void UInventory_Base::OnHovered(UObject* _Data, bool _hovered)
{
}
