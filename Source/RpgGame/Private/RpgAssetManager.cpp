// Fill out your copyright notice in the Description page of Project Settings.


#include "RpgAssetManager.h"

#include "RpgGameplayTags.h"

URpgAssetManager& URpgAssetManager::Get()
{
	check(GEngine);
	URpgAssetManager* AssetManager = Cast<URpgAssetManager>(GEngine->AssetManager);
	check(AssetManager);
	return *AssetManager;
}

void URpgAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FRpgGameplayTags::InitializeNativeGameplayTags();
}
