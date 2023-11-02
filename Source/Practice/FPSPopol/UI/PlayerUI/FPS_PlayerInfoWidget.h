// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FPS_PlayerInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API UFPS_PlayerInfoWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	class UProgressBar* m_HPBar;

public:
	void SetHPBarRatio(float _ratio);

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& _geo, float _DT) override;

};
