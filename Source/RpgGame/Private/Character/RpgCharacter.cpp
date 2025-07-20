// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RpgCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/RpgAbilitySystemComponent.h"
#include "Player/RpgPlayerController.h"
#include "Player/RpgPlayerState.h"
#include "UI/HUD/RpgHUD.h"


// Sets default values
ARpgCharacter::ARpgCharacter()
{
	
}

void ARpgCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability actor info for the server
	InitAbilityActorInfo();
	AddCharacterAbilities();
}

void ARpgCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor info for the client
	InitAbilityActorInfo();
}

int32 ARpgCharacter::GetPlayerLevel() const
{
	const ARpgPlayerState* RpgPlayerState = GetPlayerState<ARpgPlayerState>();
	check(RpgPlayerState)
	return RpgPlayerState->GetPlayerLevel();
}

void ARpgCharacter::InitAbilityActorInfo()
{
	ARpgPlayerState* RpgPlayerState = GetPlayerState<ARpgPlayerState>();
	check(RpgPlayerState)
	RpgPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(RpgPlayerState, this);

	Cast<URpgAbilitySystemComponent>(RpgPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	
	AbilitySystemComponent = RpgPlayerState->GetAbilitySystemComponent();
	AttributeSet = RpgPlayerState->GetAttributeSet();

	if (ARpgPlayerController* RpgPlayerController = Cast<ARpgPlayerController>(GetController()))
	{
		if (ARpgHUD* AuraHUD = Cast<ARpgHUD>(RpgPlayerController->GetHUD()))
		{
			AuraHUD->InitOverlay(RpgPlayerController, RpgPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
	InitializeDefaultAttribute();
}


