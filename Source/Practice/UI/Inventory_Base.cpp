// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory_Base.h"

#include "../Header/GlobalHeader.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"

#include "ToolTip_Base.h"
#include "../System/InvenItemData.h"

void UInventory_Base::NativeConstruct()
{
	Super::NativeConstruct();

	m_ListView = Cast<UListView>(GetWidgetFromName(TEXT("InvenListView")));

	if (!IsValid(m_ListView))
	{
		LOG(LogTemp, Error, TEXT("ListView Lost"));
	}
	else
	{
		// Tooltip_Base 를 상속받은 Tooltip Blueprint 클래스정보 가져오기
		UBlueprintGeneratedClass* TooltipClass = LoadObject<UBlueprintGeneratedClass>(nullptr, TEXT("Script/UMGEditor.WidgetBlueprint'/Game/MyCharacter/Character/UI/InventoryUI/UI_ToolTip_Base.UI_ToolTip_Base_C'"));
		if (IsValid(TooltipClass))
		{
			// Blueprint 클래스정보로 실제 객체하나 만들어서 ListView 의 Tooltip 용으로 전달하기
			m_ListView->SetToolTip(CreateWidget(GetWorld(), TooltipClass));

			// 리스트뷰 항목(아이템) 위로 마우스가 올라가거나 벗어날 때 호출될 함수 바인딩
			m_ListView->OnItemIsHoveredChanged().AddUObject(this, &UInventory_Base::OnHovered);
		}
	}
}

void UInventory_Base::NativeTick(const FGeometry& _geo, float _DT)
{
	Super::NativeTick(_geo, _DT);
}

void UInventory_Base::OnHovered(UObject* _Data, bool _hovered)
{
	if (_hovered)
	{
		// 마우스 호버한 아이템 위젯과 연결되어있는 데이터 가져옴
		UInvenItemData* pData = Cast<UInvenItemData>(_Data);

		// ListView 에 넣어둔 툴팁용 위젯 객체 가져옴
		UToolTip_Base* pTooltip = Cast<UToolTip_Base>(m_ListView->ToolTipWidget);

		// 툴팁 위젯의 TextBlock 에 Item Description 정보 문자열 전달
		pTooltip->GetTextBlock()->SetText(FText::FromString(pData->GetItemDescription()));

		// 툴팁 위젯 시각화
		m_ListView->ToolTipWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		m_ListView->ToolTipWidget->SetVisibility(ESlateVisibility::Hidden);
	}
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