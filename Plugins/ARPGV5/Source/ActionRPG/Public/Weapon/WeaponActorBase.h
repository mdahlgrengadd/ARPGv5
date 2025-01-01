// WeaponActor.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponActorBase.generated.h"

UCLASS()
class ACTIONRPG_API AWeaponActorBase : public AActor
{
    GENERATED_BODY()

public:
    AWeaponActorBase();

    // Called when weapon is equipped
    UFUNCTION(BlueprintCallable, Category = "Weapon")
    virtual void OnEquipped();

    // Called when weapon is unequipped
    UFUNCTION(BlueprintCallable, Category = "Weapon")
    virtual void OnUnequipped();

    // The skeletal mesh component for the weapon
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
    TObjectPtr<USkeletalMeshComponent> WeaponMesh;

    // The socket name to attach to on the character
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
    FName AttachSocketName;

protected:
    virtual void BeginPlay() override;
};

