// RPGCharacter.h
#pragma once

#include "CoreMinimal.h"
#include "RPGCharacterBase.h"
#include "Weapon/WeaponActorBase.h"
#include "RPGCharacter.generated.h"

class UAnimMontage;

/**
 * C++ base implementation of character with full Blueprint support
 * All functions can be overridden and variables accessed in Blueprint children
 */
UCLASS(Blueprintable, BlueprintType)
class ARPGCharacter : public ARPGCharacterBase
{
    GENERATED_BODY()

public:
    ARPGCharacter();

    // Combat Functions - All made BlueprintNativeEvent so they can be overridden
    /** Attempts to perform a melee attack using the current weapon */
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Attack")
    bool DoMeleeAttack();
    virtual bool DoMeleeAttack_Implementation();

    /** Attempts to perform a skill attack */
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Attack")
    bool DoSkillAttack();
    virtual bool DoSkillAttack_Implementation();

    /** Uses a potion item from the inventory */
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Items")
    void UseItemPotion();
    virtual void UseItemPotion_Implementation();

    // State Check Functions - All made BlueprintNativeEvent
    /** Returns true if currently playing a high priority montage */
    UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "Animation")
    bool IsPlayingHighPriorityMontage() const;
    virtual bool IsPlayingHighPriorityMontage_Implementation() const;

    /** Returns true if currently performing a melee attack */
    UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "Animation")
    bool IsUsingMelee() const;
    virtual bool IsUsingMelee_Implementation() const;

    /** Returns true if currently using a skill */
    UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "Animation")
    bool IsUsingSkill() const;
    virtual bool IsUsingSkill_Implementation() const;

    /** Returns true if the character can use abilities (not dead/stunned) */
    UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "Abilities")
    bool CanUseAnyAbility() const;
    virtual bool CanUseAnyAbility_Implementation() const;

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Health")
    bool isAlive() const;

    /** Plays a montage with high priority, preventing other animations */
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Animation")
    void PlayHighPriorityMontage(UAnimMontage* Montage, FName StartSection = NAME_None);
    virtual void PlayHighPriorityMontage_Implementation(UAnimMontage* Montage, FName StartSection = NAME_None);

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    // Equipment Properties
    /** Currently equipped weapon */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
    TObjectPtr<AWeaponActorBase> CurrentWeapon;

    /** Current weapon equipment slot */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack", meta = (ExposeOnSpawn = "true"))
    FRPGItemSlot CurrentWeaponSlot;

    // Combat Properties
    /** Counter for attack delay timing */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack", meta = (ExposeOnSpawn = "true"))
    int32 AttackDelayCount;

    /** Time between attacks */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack", meta = (ExposeOnSpawn = "true"))
    float AttackDelayTime;

    /** Starting section name for melee attack animations */
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
    FName MeleeStartSection;

    // Character State Properties
    /** Whether the character is currently invincible */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (ExposeOnSpawn = "true"))
    bool bInvincible;

    /** Whether the character is protected by a shield */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (ExposeOnSpawn = "true"))
    bool IsProtectedByShield;

    /** Whether the character is currently stunned */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (ExposeOnSpawn = "true"))
    bool bStunned;

    /** Event triggered when using a skill */
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSkillAttackSignature);

    /** Broadcast when a skill attack is successfully activated */
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnSkillAttackSignature OnSkillAttack;

protected:
    /** Currently playing high priority montage */
    UPROPERTY(BlueprintReadWrite, Category = "Animation")
    TObjectPtr<UAnimMontage> HighPriorityMontage;

    /** Delayed character destruction helper */
    UFUNCTION(BlueprintCallable, Category = "Character")
    virtual void DelayedDestroy();
};
