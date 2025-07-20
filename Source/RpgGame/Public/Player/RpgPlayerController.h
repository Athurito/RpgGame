// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RpgPlayerController.generated.h"

class UDamageTextComponent;
class URpgAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class RPGGAME_API ARpgPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ARpgPlayerController();

	UFUNCTION(Client, Reliable)
	void ShowDamageNumber(const float DamageAmount, ACharacter* TargetCharacter);

	UPROPERTY()
	TObjectPtr<URpgAbilitySystemComponent> AuraAbilitySystemComponent;

	URpgAbilitySystemComponent* GetAsc();


	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageTextComponent> DamageTextComponentClass;
};
