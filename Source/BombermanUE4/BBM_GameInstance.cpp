// Fill out your copyright notice in the Description page of Project Settings.


#include "BBM_GameInstance.h"
#include "Engine/Engine.h"

void UBBM_GameInstance::PostInitProperties()
{
	Super::PostInitProperties();
	if (GEngine != nullptr)
	{
		GEngine->OnNetworkFailure().AddUObject(this, &UBBM_GameInstance::HandleNetworkFailure);
	}
}

void UBBM_GameInstance::BeginDestroy()
{
	Super::BeginDestroy();
	if (GEngine != nullptr)
	{
		GEngine->OnNetworkFailure().RemoveAll(this);
	}
}

void UBBM_GameInstance::HandleNetworkFailure(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString)
{
	UE_LOG(LogTemp, Warning, TEXT("Erro de rede descrito da seguinte forma: %s"), *ErrorString);
}
