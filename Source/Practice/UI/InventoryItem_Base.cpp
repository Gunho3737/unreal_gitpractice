// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItem_Base.h"

#include "../Header/GlobalHeader.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "../System/InvenItemData.h"


void UInventoryItem_Base::InitFromData(UObject* _Data)
{
	UInvenItemData* pItemData = Cast<UInvenItemData>(_Data);
	if (!IsValid(pItemData))
	{
		LOG(LogTemp, Error, TEXT("Inventory item base Initfrom data fail"));
		return;
	}

	// 아이콘 이미지 세팅
	FString IconPath = pItemData->GetIconImgPath();
	UTexture2D* pTex2D = LoadObject<UTexture2D>(nullptr, *IconPath);
	m_IconImg->SetBrushFromTexture(pTex2D);

	// 아이템 이름 세팅
	m_ItemName->SetText(FText::FromString(pItemData->GetItemName()));

	// 아이템 수량 세팅
	m_ItemCount->SetText(FText::FromString(FString::Printf(TEXT("%d"), pItemData->GetItemCount())));
}

void UInventoryItem_Base::NativeConstruct()
{
	Super::NativeConstruct();

	m_IconImg = Cast<UImage>(GetWidgetFromName(TEXT("IconImage")));
	m_ItemName = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemName")));
	m_ItemCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("Count")));

	if (!IsValid(m_IconImg) || !IsValid(m_ItemName) || !IsValid(m_ItemCount))
	{
		LOG(LogTemp, Error, TEXT("Inventory Item Base WidgetFind Fail"));
	}
}

void UInventoryItem_Base::NativeTick(const FGeometry& _geo, float _DT)
{
	Super::NativeTick(_geo, _DT);
}

