// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RpgPlayerState.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/RpgAbilitySystemComponent.h"
#include "AbilitySystem/RpgAttributeSet.h"
#include "Net/UnrealNetwork.h"

ARpgPlayerState::ARpgPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<URpgAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<URpgAttributeSet>("AttributeSet");
	SetNetUpdateFrequency(100.f);
}

void ARpgPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ARpgPlayerState, Level);
}

UAbilitySystemComponent* ARpgPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

int32 ARpgPlayerState::GetPlayerLevel() const
{
	return Level;
}

void ARpgPlayerState::OnRep_Level(int32 OldLevel)
{
}
