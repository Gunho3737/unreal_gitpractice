// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItem_Base.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API UInventoryItem_Base : public UUserWidget
{
	GENERATED_BODY()

private:
	class UTextBlock* m_ItemName;
	class UTextBlock* m_ItemCount;
	class UImage* m_IconImg;


public:
	// InventoryItemData �� �Է¹޾Ƽ� �ʱ�ȭ�ϴ� �Լ�
	UFUNCTION(BlueprintCallable)
	void InitFromData(UObject* _Data);

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& _geo, float _DT) override;
};
