// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RpgCharacterBase.h"

#include "RpgGame.h"
#include "AbilitySystem/RpgAbilitySystemComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"


class URpgAbilitySystemComponent;
// Sets default values
ARpgCharacterBase::ARpgCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);


	PrimaryWeapon = CreateDefaultSubobject<USkeletalMeshComponent>("PrimaryWeapon");
	PrimaryWeapon->SetupAttachment(GetMesh(), FName("PrimaryWeaponSocket"));
	PrimaryWeapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	PrimaryStartArrow = CreateDefaultSubobject<UArrowComponent>("PrimaryStart");
	PrimaryStartArrow->SetupAttachment(PrimaryWeapon);

	PrimaryEndArrow = CreateDefaultSubobject<UArrowComponent>("PrimaryEnd");
	PrimaryEndArrow->SetupAttachment(PrimaryWeapon);

	SecondaryWeapon = CreateDefaultSubobject<USkeletalMeshComponent>("SecondaryWeapon");
	SecondaryWeapon->SetupAttachment(GetMesh(), FName("SecondaryWeaponSocket"));
	SecondaryWeapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SecondaryStartArrow = CreateDefaultSubobject<UArrowComponent>("SecondaryStart");
	SecondaryStartArrow->SetupAttachment(SecondaryWeapon);

	SecondaryEndArrow = CreateDefaultSubobject<UArrowComponent>("SecondaryEnd");
	SecondaryEndArrow->SetupAttachment(SecondaryWeapon);
}

// Called when the game starts or when spawned
void ARpgCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

UAbilitySystemComponent* ARpgCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAnimMontage* ARpgCharacterBase::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}

void ARpgCharacterBase::Death()
{
	SecondaryWeapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	MulticastHandleDeath();
}

void ARpgCharacterBase::MulticastHandleDeath_Implementation()
{
	PrimaryWeapon->SetSimulatePhysics(true);
	PrimaryWeapon->SetEnableGravity(true);
	PrimaryWeapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	
	SecondaryWeapon->SetSimulatePhysics(true);
	SecondaryWeapon->SetEnableGravity(true);
	SecondaryWeapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Dissolve();
}

FVector ARpgCharacterBase::GetSecondaryWeaponSocketLocation()
{
	check(SecondaryWeapon);
	return SecondaryWeapon->GetSocketLocation(WeaponTipSocketName);
}

void ARpgCharacterBase::InitAbilityActorInfo()
{
}

void ARpgCharacterBase::ApplyEffectToSelf(const TSubclassOf<UGameplayEffect>& GameplayEffectClass, const float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(DefaultPrimaryAttributes);
	
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void ARpgCharacterBase::InitializeDefaultAttribute() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}

void ARpgCharacterBase::AddCharacterAbilities()
{
	if (!HasAuthority())
		return;
	
	URpgAbilitySystemComponent* RpgAsc = CastChecked<URpgAbilitySystemComponent>(AbilitySystemComponent);
	RpgAsc->AddCharacterAbilities(StartupAbilities);
}

void ARpgCharacterBase::Dissolve()
{
	if (IsValid(DissolveMaterialInstance))
	{
		UMaterialInstanceDynamic* DynamicMaterialInstance = UMaterialInstanceDynamic::Create(DissolveMaterialInstance, this);
		GetMesh()->SetMaterial(0, DynamicMaterialInstance);

		StartDissolveTimeLine(DynamicMaterialInstance);
	}
	if (IsValid(WeaponDissolveMaterialInstance))
	{
		UMaterialInstanceDynamic* DynamicMaterialInstance = UMaterialInstanceDynamic::Create(WeaponDissolveMaterialInstance, this);
		SecondaryWeapon->SetMaterial(0, DynamicMaterialInstance);

		StartWeaponDissolveTimeLine(DynamicMaterialInstance);
	}
}