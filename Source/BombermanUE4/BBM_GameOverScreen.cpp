// Fill out your copyright notice in the Description page of Project Settings.


#include "BBM_GameOverScreen.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

UBBM_GameOverScreen::UBBM_GameOverScreen(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

#pragma optimize ("", off)

bool UBBM_GameOverScreen::Initialize()
{
	if (Super::Initialize())
	{
		m_BtnBackToMenu = Cast<UButton>(GetWidgetFromName(FName(TEXT("Btn_BackToMenu"))));

		if (m_BtnBackToMenu != nullptr) m_BtnBackToMenu->OnClicked.AddDynamic(this, &UBBM_GameOverScreen::ReturnToMainMenu);

		return true;
	}
	return false;
}

void UBBM_GameOverScreen::ReturnToMainMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), m_MapMainMenuName);
}

#pragma optimize ("", on)
