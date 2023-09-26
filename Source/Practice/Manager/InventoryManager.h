// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../Header/GlobalHeader.h"
#include "InventoryManager.generated.h"



USTRUCT()
struct FItemStack
{
	GENERATED_BODY();

	FGameItemInfo* ItemInfo;
	int32			Stack;
};



/**
 * 
 */
UCLASS()
class PRACTICE_API UInventoryManager : public UObject
{
	GENERATED_BODY()
	
};
