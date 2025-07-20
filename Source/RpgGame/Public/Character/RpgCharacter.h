// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RpgCharacterBase.h"
#include "RpgCharacter.generated.h"

UCLASS()
class RPGGAME_API ARpgCharacter : public ARpgCharacterBase
{
	GENERATED_BODY()
public:
	ARpgCharacter();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	//~ Combat Interface
	virtual int32 GetPlayerLevel() const override;
	//~ end Combat Interface
private:
	virtual void InitAbilityActorInfo() override;
};
