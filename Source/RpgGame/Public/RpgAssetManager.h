// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "RpgAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API URpgAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:

	static URpgAssetManager& Get();

protected:

	virtual void StartInitialLoading() override;
};
