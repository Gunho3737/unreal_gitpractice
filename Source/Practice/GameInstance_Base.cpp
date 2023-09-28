// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance_Base.h"
#include "Manager/InventoryManager.h"

UGameInstance_Base::UGameInstance_Base()
	: m_InvenMgr(nullptr)
{

	ConstructorHelpers::FObjectFinder<UDataTable> tablefinder(TEXT("/Script/Engine.DataTable'/Game/MyCharacter/Item/DT_ItemInfo.DT_ItemInfo'"));
	if (tablefinder.Succeeded())
	{
		UInventoryManager::GetInst(this)->SetGameItemDataTable(tablefinder.Object);
	}
	else
	{
		LOG(LogTemp, Error, TEXT("Game Item data Table error"));
	}
}

UGameInstance_Base::~UGameInstance_Base()
{
}
