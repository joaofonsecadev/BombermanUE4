// Fill out your copyright notice in the Description page of Project Settings.


#include "MPT_DamageTrigger.h"
#include "MPT_Character.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"

AMPT_DamageTrigger::AMPT_DamageTrigger()
{
	OnActorBeginOverlap.AddDynamic(this, &AMPT_DamageTrigger::OverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &AMPT_DamageTrigger::OverlapEnd);
}

void AMPT_DamageTrigger::OverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (HasAuthority())
	{
		if (this != OtherActor)
		{
			UGameplayStatics::ApplyDamage(OtherActor, 5, OtherActor->GetInstigatorController(), this, UDamageType::StaticClass());
		}
	}
}

void AMPT_DamageTrigger::OverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{

}
