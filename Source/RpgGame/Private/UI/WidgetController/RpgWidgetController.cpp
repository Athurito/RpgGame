// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/RpgWidgetController.h"

void URpgWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& Params)
{
	PlayerController = Params.PlayerController;
	PlayerState = Params.PlayerState;
	AbilitySystemComponent = Params.AbilitySystemComponent;
	AttributeSet = Params.AttributeSet;
}

void URpgWidgetController::BroadcastInitialValues()
{
}

void URpgWidgetController::BindCallBacksToDependencies()
{
}
