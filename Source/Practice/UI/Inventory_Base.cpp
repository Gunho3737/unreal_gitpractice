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
		// Tooltip_Base �� ��ӹ��� Tooltip Blueprint Ŭ�������� ��������
		UBlueprintGeneratedClass* TooltipClass = LoadObject<UBlueprintGeneratedClass>(nullptr, TEXT("Script/UMGEditor.WidgetBlueprint'/Game/MyCharacter/Character/UI/InventoryUI/UI_ToolTip_Base.UI_ToolTip_Base_C'"));
		if (IsValid(TooltipClass))
		{
			// Blueprint Ŭ���������� ���� ��ü�ϳ� ���� ListView �� Tooltip ������ �����ϱ�
			m_ListView->SetToolTip(CreateWidget(GetWorld(), TooltipClass));

			// ����Ʈ�� �׸�(������) ���� ���콺�� �ö󰡰ų� ��� �� ȣ��� �Լ� ���ε�
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
		// ���콺 ȣ���� ������ ������ ����Ǿ��ִ� ������ ������
		UInvenItemData* pData = Cast<UInvenItemData>(_Data);

		// ListView �� �־�� ������ ���� ��ü ������
		UToolTip_Base* pTooltip = Cast<UToolTip_Base>(m_ListView->ToolTipWidget);

		// ���� ������ TextBlock �� Item Description ���� ���ڿ� ����
		pTooltip->GetTextBlock()->SetText(FText::FromString(pData->GetItemDescription()));

		// ���� ���� �ð�ȭ
		m_ListView->ToolTipWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		m_ListView->ToolTipWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UInventory_Base::AddItem(UObject* _ItemData)
{
	//listview�� ��ü �Լ� ȣ��
	m_ListView->AddItem(_ItemData);
}

void UInventory_Base::Clear()
{
	m_ListView->ClearListItems();
}