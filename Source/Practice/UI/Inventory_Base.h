// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inventory_Base.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API UInventory_Base : public UUserWidget
{
	GENERATED_BODY()

private:
	class UListView* m_ListView;


public:
	void AddItem(UObject* _ItemData);
	void Clear();



public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& _geo, float _DT) override;

	void OnHovered(UObject* _Data, bool _hovered);
};
