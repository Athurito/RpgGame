// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/RpgHUD.h"

#include "CommonUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "UI/Widget/RpgUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* ARpgHUD::GetOverlayWidgetController(const FWidgetControllerParams& Params)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);

		OverlayWidgetController->SetWidgetControllerParams(Params);
		OverlayWidgetController->BindCallBacksToDependencies();
	}

	return OverlayWidgetController;
}

void ARpgHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{

	checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass uninitialized, please fill out BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass uninitialized, please fill out BP_AuraHUD"));
	
	UCommonUserWidget* Widget = CreateWidget<UCommonUserWidget>(GetWorld(), OverlayWidgetClass);

	OverlayWidget = Cast<URpgUserWidget>(Widget);

	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();
	Widget->AddToViewport();
	
}
