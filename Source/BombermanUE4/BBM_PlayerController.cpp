// Fill out your copyright notice in the Description page of Project Settings.


#include "BBM_PlayerController.h"
#include "Kismet/GameplayStatics.h"

void ABBM_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("RestartLevel", IE_Released, this, &ABBM_PlayerController::RestartLevel);
	InputComponent->BindAction("ExitLevel", IE_Released, this, &ABBM_PlayerController::ExitLevel);
}

void ABBM_PlayerController::RestartServerLevel_Implementation()
{
	if (HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("Calling for a level restart."));
		UWorld* World = GetWorld();
		if (World != nullptr)
		{
			World->ServerTravel("/Game/BombermanUE4/Maps/Main");
		}
	}
}

void ABBM_PlayerController::ExitLevel()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling for a level exit."));
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
}
