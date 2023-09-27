// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory_Base.h"

#include "../Header/GlobalHeader.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"

void UInventory_Base::NativeConstruct()
{
	Super::NativeConstruct();

	m_ListView = Cast<UListView>(GetWidgetFromName(TEXT("InvenListView")));

	if (!IsValid(m_ListView))
	{
		LOG(LogTemp, Error, TEXT("ListView Lost"));
	}
}

void UInventory_Base::NativeTick(const FGeometry& _geo, float _DT)
{
	Super::NativeTick(_geo, _DT);
}

void UInventory_Base::OnHovered(UObject* _Data, bool _hovered)
{
}

void UInventory_Base::AddItem(UObject* _ItemData)
{
	//listview의 자체 함수 호출
	m_ListView->AddItem(_ItemData);
}

void UInventory_Base::Clear()
{
	m_ListView->ClearListItems();
}