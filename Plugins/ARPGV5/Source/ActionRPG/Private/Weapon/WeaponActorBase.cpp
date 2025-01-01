// WeaponActor.cpp
#include "Weapon\WeaponActorBase.h"
#include "Components/SkeletalMeshComponent.h"

AWeaponActorBase::AWeaponActorBase()
{
    PrimaryActorTick.bCanEverTick = false;

    // Create and setup the weapon mesh
    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
    RootComponent = WeaponMesh;

    // Default socket name
    AttachSocketName = FName("WeaponSocket");
}

void AWeaponActorBase::BeginPlay()
{
    Super::BeginPlay();
}

void AWeaponActorBase::OnEquipped()
{
    // Blueprint implementable
}

void AWeaponActorBase::OnUnequipped()
{
    // Blueprint implementable
}