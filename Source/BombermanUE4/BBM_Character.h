#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BBM_DestructibleObject.h"
#include "BBM_Bomb.h"
#include "BBM_Character.generated.h"

UCLASS(config = Game)
class ABBM_Character : public ACharacter, public IBBM_DestructibleObject
{
	GENERATED_BODY()

public:
	ABBM_Character();
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(Client, Unreliable)
	virtual void DestroySelf() override;

	UFUNCTION()
	void IncreaseAmmo();

	int32 Ammo = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	UPROPERTY(EditAnywhere, Category = "References")
	TSubclassOf<AActor> Bomb;

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	UFUNCTION(Server, Reliable)
	void PlaceBomb();

	UFUNCTION(Server, Reliable)
	void RestartServerLevel();

	UFUNCTION(Server, Reliable)
	void SetPlayerAsDying();

	UFUNCTION()
	void OnRep_bIsDying();

	UPROPERTY(ReplicatedUsing = OnRep_bIsDying)
	bool bIsDying = false;

	bool bIsDead = false;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
};