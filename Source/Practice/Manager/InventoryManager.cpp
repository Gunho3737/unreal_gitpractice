// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryManager.h"
#include "../GameInstance_Base.h"

#include "../PracticeGameModeBase.h"
#include "../UI/MainHUDWidget.h"
#include "../UI/Inventory_Base.h"
#include "../System/InvenItemData.h"


UWorld* UInventoryManager::m_World = nullptr;

UInventoryManager* UInventoryManager::GetInst(UWorld* _World)
{
	m_World = _World;

	return GetInst(m_World->GetGameInstance());
}

UInventoryManager* UInventoryManager::GetInst(UGameInstance* _GameInst)
{
	UGameInstance_Base* pGameInst = Cast<UGameInstance_Base>(_GameInst);

	if (!IsValid(pGameInst->m_InvenMgr))
	{
		pGameInst->m_InvenMgr = NewObject<UInventoryManager>();
		pGameInst->m_InvenMgr->AddToRoot();
	}

	return pGameInst->m_InvenMgr;
}

void UInventoryManager::SetGameItemDataTable(UDataTable* _ItemDataTable)
{
	m_ItemTable = _ItemDataTable;

	// ������ ���̺� �ȿ��ִ� ��� ������ TArray �� �ִ´�.
	FString str;
	TArray<FGameItemInfo*>	arrTableData;
	m_ItemTable->GetAllRows<FGameItemInfo>(str, arrTableData);

	// ���̺� �ȿ� �ִ� ������ ������ ������ ID �� Key �� �ϴ� TMap �� �ִ´�.
	for (int32 i = 0; i < arrTableData.Num(); ++i)
	{
		m_mapItemInfo.Add(arrTableData[i]->ID, *arrTableData[i]);
	}
}

void UInventoryManager::AddGameItem(EITEM_ID _ID)
{
	// ������ ������ ���̵� �ش��ϴ� ������ ������ �����´�.
	FGameItemInfo* pItemInfo = m_mapItemInfo.Find(_ID);

	if (nullptr == pItemInfo)
	{
		LOG(LogTemp, Error, TEXT("ITME ID �� �ش��ϴ� ������ ���� ã�� �� ����"));
		return;
	}


	// ������ Ÿ�Կ� �´� ���ѿ� ���� ��, �ش� �������� �̹� �����ϰ��ִ��� Ȯ��
	FItemStack* pItemStack = m_BackPack[(int32)pItemInfo->TYPE].Find(_ID);

	if (nullptr == pItemStack)
	{
		m_BackPack[(int32)pItemInfo->TYPE].Add(_ID, FItemStack{ pItemInfo , 1 });
	}
	else
	{
		++pItemStack->Stack;
	}

	// ���� ���Ӹ�带 üũ
	APracticeGameModeBase* GameMode = Cast<APracticeGameModeBase>(UGameplayStatics::GetGameMode(m_World));
	if (!IsValid(GameMode))
	{
		return;
	}

	// ���Ӹ��� ���� ���� HUD ��������
	UMainHUDWidget* MainHUD = GameMode->GetMainHUD();

	// �κ��丮 UI �� ���������� ������ �ٽ� ����
	if (MainHUD->IsInventoryOpen())
	{
		ResetWidget();
	}
}

void UInventoryManager::OpenInventoryUI()
{
	APracticeGameModeBase* GameMode = Cast<APracticeGameModeBase>(UGameplayStatics::GetGameMode(m_World));
	if (!IsValid(GameMode))
	{
		return;
	}

	// ���Ӹ��� ���� ���� HUD ��������
	UMainHUDWidget* MainHUD = GameMode->GetMainHUD();

	ResetWidget();

	// InventoryWidget Visible
	MainHUD->ShowInventoryUI(true);

	// �÷��̾� ��Ʈ�ѷ��� �Է¸�带 UI ���� ��ȯ�Ѵ�.
	APlayerController* pController = m_World->GetFirstPlayerController();

	FInputModeUIOnly uionly{};
	pController->SetInputMode(uionly);
	pController->bShowMouseCursor = true;
}

void UInventoryManager::CloseInventoryUI()
{
	APracticeGameModeBase* GameMode = Cast<APracticeGameModeBase>(UGameplayStatics::GetGameMode(m_World));
	if (!IsValid(GameMode))
		return;

	// ���Ӹ��� ���� ���� HUD ��������
	UMainHUDWidget* MainHUD = GameMode->GetMainHUD();

	// �κ��丮 ���� �ð�ȭ ����
	MainHUD->ShowInventoryUI(false);

	// �÷��̾� ��Ʈ�ѷ��� �Է¸�带 Game ���� ��ȯ�Ѵ�.
	APlayerController* pController = m_World->GetFirstPlayerController();

	FInputModeGameOnly gonly{};
	pController->SetInputMode(gonly);
	pController->bShowMouseCursor = false;


}

void UInventoryManager::ResetWidget()
{
	APracticeGameModeBase* GameMode = Cast<APracticeGameModeBase>(UGameplayStatics::GetGameMode(m_World));
	if (!IsValid(GameMode))
		return;

	// ���Ӹ��� ���� ���� HUD ��������
	UMainHUDWidget* MainHUD = GameMode->GetMainHUD();

	// MainHUD �κ��� InventoryWidget(UI) ��������
	UInventory_Base* InventoryWidget = MainHUD->GetInventoryWidget();

	// InventoryWidget(UI) ���� ���� Ŭ�����ϱ�
	InventoryWidget->Clear();

	for (int32 i = 0; i < (int32)EITEM_TYPE::END; ++i)
	{
		for (auto Iterator = m_BackPack[i].CreateConstIterator(); Iterator; ++Iterator)
		{
			UInvenItemData* pData = NewObject<UInvenItemData>();

			pData->SetIconImgPath(Iterator.Value().ItemInfo->IconPath);
			pData->SetItemName(Iterator.Value().ItemInfo->Description);
			pData->SetItemDescription(Iterator.Value().ItemInfo->Description);
			pData->SetItemCount(Iterator.Value().Stack);

			InventoryWidget->AddItem(pData);
		}
	}
}
