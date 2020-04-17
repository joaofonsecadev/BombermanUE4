// Fill out your copyright notice in the Description page of Project Settings.


#include "BBM_UI_MainMenu.h"
#include "BBM_UI_ConnectToIP.h"
#include "Components/Button.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

UBBM_UI_MainMenu::UBBM_UI_MainMenu(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

bool UBBM_UI_MainMenu::Initialize()
{
	if (Super::Initialize())
	{
		m_BtnHostMatch = Cast<UButton>(GetWidgetFromName(FName(TEXT("Btn_HostMatch"))));
		m_BtnJoinMatch = Cast<UButton>(GetWidgetFromName(FName(TEXT("Btn_JoinMatch"))));
		m_BtnExitGame = Cast<UButton>(GetWidgetFromName(FName(TEXT("Btn_ExitGame"))));

		if (m_BtnHostMatch != nullptr) m_BtnHostMatch->SetIsEnabled(false);
		if (m_BtnJoinMatch != nullptr) m_BtnJoinMatch->OnClicked.AddDynamic(this, &UBBM_UI_MainMenu::ShowConnectToIPUI);
		if (m_BtnExitGame != nullptr) m_BtnExitGame->OnClicked.AddDynamic(this, &UBBM_UI_MainMenu::ExitGame);

		return true;
	}
	return false;
}

void UBBM_UI_MainMenu::ShowConnectToIPUI()
{
	ConnectToIP = CreateWidget(this, ConnectToIP_BP);
	if (ConnectToIP != nullptr)
	{
		UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
		ConnectToIP->AddToViewport();
		UE_LOG(LogTemp, Warning, TEXT("Hey, a UI para ligar ao IP devia estar a aparecer agora...!"));
	}
}

void UBBM_UI_MainMenu::ExitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}