// Fill out your copyright notice in the Description page of Project Settings.


#include "BBM_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "BBM_Character.h"
#include "GameFramework/Controller.h"
#include "Engine/Engine.h"
#include "UObject/NameTypes.h"
#include "Blueprint/UserWidget.h"
#include "BBM_GameOverScreen.h"
#include "Blueprint/WidgetLayoutLibrary.h"

void ABBM_PlayerController::BeginPlay()
{

}

void ABBM_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//InputComponent->BindAction("RestartLevel", IE_Released, this, &ABBM_PlayerController::RestartLevel);
	InputComponent->BindAction("ExitLevel", IE_Released, this, &ABBM_PlayerController::ExitLevel);
}

//TODO: execute server side function which can't be called from here apparently
/*
void ABBM_PlayerController::RestartServerLevel_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Going to call for a level restart."));
	if (HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("Calling for a level restart."));
		UWorld* World = GetWorld();
		if (World != nullptr)
		{
			World->ServerTravel("/Game/BombermanUE4/Maps/Main");
		}
	}
}*/

void ABBM_PlayerController::SpawnGameOverUI_Implementation(TSubclassOf<UBBM_GameOverScreen> GameOverScreen_BP)
{
	m_GameOverScreen = CreateWidget<UBBM_GameOverScreen>(GetWorld(), GameOverScreen_BP);

	if (!m_GameOverScreen)
	{
		return;
	}
	m_GameOverScreen->AddToViewport();
	bShowMouseCursor = true;
}

void ABBM_PlayerController::ExitLevel()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling for a level exit."));
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
}
