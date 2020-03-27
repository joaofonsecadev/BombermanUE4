#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BBM_Character.generated.h"

UCLASS(config = Game)
class ABBM_Character : public ACharacter
{
	GENERATED_BODY()

public:
	ABBM_Character();

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	//void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	UPROPERTY(EditAnywhere, Category = "References")
	TSubclassOf<AActor> Bomb;

	//float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:

	void MoveForward(float Value);

	void MoveRight(float Value);

	void PlaceBomb();

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	/*UFUNCTION(Server, Reliable)
	void ThrowBomb();*/

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*UFUNCTION()
	void OnRep_CurrentHealth();*/

	//void OnHealthUpdate();

	/*UPROPERTY(EditDefaultsOnly)
		float MaxHealth;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentHealth)
		float CurrentHealth;*/
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;
};