// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FPS_PlayerInfoWidget.h"
#include "FPS_MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API UFPS_MainWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UFPS_PlayerInfoWidget* m_PlayerInfo;
	class UImage* m_Crosshair;

public:
	void SetPlayerHPRatio(float _Ratio);

	void UIOff();

	UFPS_PlayerInfoWidget* GetPlayerInfoWidget() { return m_PlayerInfo; }

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& _geo, float _DT) override;
};
