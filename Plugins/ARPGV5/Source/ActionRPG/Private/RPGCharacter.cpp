// RPGCharacter.cpp
#include "RPGCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Animation/AnimInstance.h"

ARPGCharacter::ARPGCharacter()
{
    // Initialize default property values
    AttackDelayCount = 0;
    AttackDelayTime = 0.04f;
    bInvincible = false;
    IsProtectedByShield = false;
    bStunned = false;

    // Make sure the character ticks every frame
    PrimaryActorTick.bCanEverTick = true;
}

void ARPGCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void ARPGCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

bool ARPGCharacter::DoMeleeAttack_Implementation()
{
    // Check if we can use abilities and aren't already attacking
    if (!CanUseAnyAbility() || IsUsingMelee())
    {
        return false;
    }

    // Activate the weapon slot ability
    return ActivateAbilitiesWithItemSlot(CurrentWeaponSlot, true);
}

bool ARPGCharacter::DoSkillAttack_Implementation()
{
    // Check if we can use abilities
    if (!CanUseAnyAbility())
    {
        return false;
    }

    // Create skill ability tag container
    FGameplayTagContainer SkillTag;
    SkillTag.AddTag(FGameplayTag::RequestGameplayTag(TEXT("Ability.Skill")));

    // Try to activate the skill ability
    bool bSuccess = ActivateAbilitiesWithTags(SkillTag, true);
    if (bSuccess)
    {
        OnSkillAttack.Broadcast();
    }
    return bSuccess;
}

void ARPGCharacter::UseItemPotion_Implementation()
{
    // Create potion slot
    FRPGItemSlot PotionSlot;
    PotionSlot.ItemType = FPrimaryAssetType(TEXT("Potion"));
    PotionSlot.SlotNumber = 0;

    // Activate potion ability
    ActivateAbilitiesWithItemSlot(PotionSlot, true);
}

bool ARPGCharacter::IsPlayingHighPriorityMontage_Implementation() const
{
    USkeletalMeshComponent* CharacterMesh = GetMesh();
    if (CharacterMesh)
    {
        UAnimInstance* AnimInst = CharacterMesh->GetAnimInstance();
        if (AnimInst)
        {
            return HighPriorityMontage && AnimInst->Montage_IsPlaying(HighPriorityMontage);
        }
    }
    return false;
}

bool ARPGCharacter::IsUsingMelee_Implementation() const
{
    TArray<URPGGameplayAbility*> ActiveAbilities;
    FGameplayTagContainer MeleeTag;
    MeleeTag.AddTag(FGameplayTag::RequestGameplayTag(TEXT("Ability.Melee")));

    // Since GetActiveAbilitiesWithTags isn't const in base class, we need to const_cast
    const_cast<ARPGCharacter*>(this)->GetActiveAbilitiesWithTags(MeleeTag, ActiveAbilities);
    return ActiveAbilities.Num() > 0;
}

bool ARPGCharacter::IsUsingSkill_Implementation() const
{
    TArray<URPGGameplayAbility*> ActiveAbilities;
    FGameplayTagContainer SkillTag;
    SkillTag.AddTag(FGameplayTag::RequestGameplayTag(TEXT("Ability.Skill")));

    // Since GetActiveAbilitiesWithTags isn't const in base class, we need to const_cast
    const_cast<ARPGCharacter*>(this)->GetActiveAbilitiesWithTags(SkillTag, ActiveAbilities);
    return ActiveAbilities.Num() > 0;
}

bool ARPGCharacter::CanUseAnyAbility_Implementation() const
{
    return isAlive() && !IsPlayingHighPriorityMontage() && !bStunned;
}

bool ARPGCharacter::isAlive() const
{
    return GetHealth() > 0.0f;
}

void ARPGCharacter::PlayHighPriorityMontage_Implementation(UAnimMontage* Montage, FName StartSection)
{
    // Don't play if we're already playing this montage
    USkeletalMeshComponent* CharacterMesh = GetMesh();
    if (CharacterMesh)
    {
        UAnimInstance* AnimInst = CharacterMesh->GetAnimInstance();
        if (AnimInst && AnimInst->Montage_IsPlaying(Montage))
        {
            return;
        }
    }

    // Set the new montage and play it
    HighPriorityMontage = Montage;
    if (Montage)
    {
        PlayAnimMontage(Montage, 1.0f, StartSection);
    }
}

void ARPGCharacter::DelayedDestroy()
{
    Destroy();
}