// Fill out your copyright notice in the Description page of Project Settings.


#include "BBM_SpectatorPawn.h"
/*
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"

void ABBM_SpectatorPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("RestartLevel", IE_Released, this, &ABBM_SpectatorPawn::RestartLevel);
	PlayerInputComponent->BindAction("ExitLevel", IE_Released, this, &ABBM_SpectatorPawn::ExitLevel);
}

void ABBM_SpectatorPawn::ExitLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
}

void ABBM_SpectatorPawn::RestartLevel_Implementation()
{
	if (HasAuthority())
	{
		UWorld* World = GetWorld();
		if (World != nullptr)
		{
			World->ServerTravel("/Game/BombermanUE4/Maps/Main");
		}
	}
}*/