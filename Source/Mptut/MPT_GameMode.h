#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MPT_GameMode.generated.h"

UCLASS()
class MPTUT_API AMPT_GameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AMPT_GameMode();

	UPROPERTY(EditDefaultsOnly)
	int8 MaxPlayers = 2;
	int8 CurrentPlayers = 0;

protected:
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
};
