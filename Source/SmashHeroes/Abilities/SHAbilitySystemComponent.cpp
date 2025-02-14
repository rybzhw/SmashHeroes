﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "SHAbilitySystemComponent.h"
#include "Characters/BaseCharacter.h"
#include "SHGameplayAbility.h"
#include "AbilitySystemGlobals.h"

USHAbilitySystemComponent::USHAbilitySystemComponent() {}

void USHAbilitySystemComponent::GetActiveAbilitiesWithTags(const FGameplayTagContainer& GameplayTagContainer, TArray<USHGameplayAbility*>& ActiveAbilities)
{
	TArray<FGameplayAbilitySpec*> AbilitiesToActivate;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(GameplayTagContainer, AbilitiesToActivate, false);

	UE_LOG(LogTemp, Log, TEXT("Activatable GA Specs Matched Tags: %d"), AbilitiesToActivate.Num());

	// Iterate the list of all ability specs
	for (FGameplayAbilitySpec* Spec : AbilitiesToActivate)
	{
		// Iterate all instances on this ability spec
		TArray<UGameplayAbility*> AbilityInstances = Spec->GetAbilityInstances();

		for (UGameplayAbility* ActiveAbility : AbilityInstances)
		{
			ActiveAbilities.Add(Cast<USHGameplayAbility>(ActiveAbility));
		}
	}
}

int32 USHAbilitySystemComponent::GetDefaultAbilityLevel() const
{
	ABaseCharacter* OwnerCharacter = Cast<ABaseCharacter>(OwnerActor);

	if (OwnerCharacter)
	{
		return OwnerCharacter->GetCharacterLevel();
	}
	return 1;
}

USHAbilitySystemComponent* USHAbilitySystemComponent::GetAbilitySystemComponentFromActor(const AActor* Actor, bool LookForComponent)
{
	return Cast<USHAbilitySystemComponent>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Actor, LookForComponent));
}
