// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ToolTip_Base.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API UToolTip_Base : public UUserWidget
{
	GENERATED_BODY()
	
private:
	class UTextBlock* m_Description;

public:
	UTextBlock* GetTextBlock() { return m_Description; }

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& _geo, float _DT) override;
};
