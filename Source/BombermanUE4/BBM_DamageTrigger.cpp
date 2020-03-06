// Fill out your copyright notice in the Description page of Project Settings.


#include "BBM_DamageTrigger.h"
#include "BBM_Character.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"

ABBM_DamageTrigger::ABBM_DamageTrigger()
{
	OnActorBeginOverlap.AddDynamic(this, &ABBM_DamageTrigger::OverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &ABBM_DamageTrigger::OverlapEnd);
}

void ABBM_DamageTrigger::OverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (HasAuthority())
	{
		if (this != OtherActor)
		{
			UGameplayStatics::ApplyDamage(OtherActor, 5, OtherActor->GetInstigatorController(), this, UDamageType::StaticClass());
		}
	}
}

void ABBM_DamageTrigger::OverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{

}
