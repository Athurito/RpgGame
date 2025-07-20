// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RpgEnemy.h"

#include "RpgGameplayTags.h"
#include "AbilitySystem/RpgAbilitySystemComponent.h"
#include "AbilitySystem/RpgAbilitySystemLibrary.h"
#include "AbilitySystem/RpgAttributeSet.h"
#include "UI/Widget/RpgUserWidget.h"


// Sets default values
ARpgEnemy::ARpgEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<URpgAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<URpgAttributeSet>("AttributeSet");

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
}

void ARpgEnemy::BeginPlay()
{
	Super::BeginPlay();
	//GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	InitAbilityActorInfo();
	URpgAbilitySystemLibrary::GiveStartUpAbilities(this, AbilitySystemComponent);

	if (URpgUserWidget* RpgUserWidget = Cast<URpgUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		RpgUserWidget->SetWidgetController(this);
	}
	
	if (const URpgAttributeSet* RpgAs = Cast<URpgAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RpgAs->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			});

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RpgAs->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			});

		
		AbilitySystemComponent->RegisterGameplayTagEvent(FRpgGameplayTags::Get().Effects_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(
			this,
			&ARpgEnemy::HitReactTagChanged
		);

		OnHealthChanged.Broadcast(RpgAs->GetHealth());
		OnMaxHealthChanged.Broadcast(RpgAs->GetMaxHealth());
	}
}


int32 ARpgEnemy::GetPlayerLevel() const
{
	return Level;
}

void ARpgEnemy::Death()
{
	SetLifeSpan(LifeSpan);
	Super::Death();
}

void ARpgEnemy::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
}



void ARpgEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<URpgAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	//TODO: Temp solution
	InitializeDefaultAttribute();
}

void ARpgEnemy::InitializeDefaultAttribute() const
{
	URpgAbilitySystemLibrary::InitializeDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);
}
