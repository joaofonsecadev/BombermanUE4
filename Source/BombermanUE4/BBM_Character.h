#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BBM_DestructibleObject.h"
#include "BBM_Character.generated.h"

UCLASS(config = Game)
class ABBM_Character : public ACharacter, public IBBM_DestructibleObject
{
	GENERATED_BODY()

public:
	ABBM_Character();

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	virtual void DestroySelf() override;

	UPROPERTY(EditAnywhere, Category = "References")
	TSubclassOf<AActor> Bomb;

	int32 Ammo = 1;

protected:

	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);
	void ExitLevel();

	UFUNCTION(Server, Reliable)
	void PlaceBomb();

	UFUNCTION(Server, Reliable)
	void RestartLevel();



	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void IncreaseAmmo();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;
};