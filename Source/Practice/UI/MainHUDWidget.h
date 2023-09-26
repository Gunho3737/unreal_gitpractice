// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Header/GlobalHeader.h"
#include "Blueprint/UserWidget.h"
#include "Inventory_Base.h"
#include "PlayerInfoWidget.h"

#include "CoreMinimal.h"
#include "MainHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API UMainHUDWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPlayerInfoWidget* m_PlayerInfo;
	UInventory_Base* m_Inventory;

public:
	UPlayerInfoWidget* GetPlayerInfoWidget() { return m_PlayerInfo; }
	UInventory_Base* GetInventoryWidget() { return m_Inventory; }

	void ShowInventoryUI(bool _bShow);
	bool IsInventoryOpen();


	void SetPlayerHPRatio(float _Ratio);

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& _geo, float _DT) override;
	
};
