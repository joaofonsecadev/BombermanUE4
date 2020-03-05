// Fill out your copyright notice in the Description page of Project Settings.


#include "MPT_GameInstance.h"
#include "Engine/Engine.h"

void UMPT_GameInstance::PostInitProperties()
{
	Super::PostInitProperties();
	if (GEngine != nullptr)
	{
		GEngine->OnNetworkFailure().AddUObject(this, &UMPT_GameInstance::HandleNetworkFailure);
	}
}

void UMPT_GameInstance::BeginDestroy()
{
	Super::BeginDestroy();
	if (GEngine != nullptr)
	{
		GEngine->OnNetworkFailure().RemoveAll(this);
	}
}

void UMPT_GameInstance::HandleNetworkFailure(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString)
{
	UE_LOG(LogTemp, Warning, TEXT("Erro de rede descrito da seguinte forma: %s"), *ErrorString);
}
