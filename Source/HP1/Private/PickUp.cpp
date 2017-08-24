// Fill out your copyright notice in the Description page of Project Settings.

#include "HP1.h"
#include "MyCharacter.h"
#include "PickUp.h"

APickUp::APickUp()
{
	InteractableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	InteractableMesh->SetSimulatePhysics(true);

	ItemName = FString("Place Item Name here");
	InteractableHelpText = FString("Press E to Pickup Item");
	Value = 0;

}

void APickUp::BeginPlay()
{
	InteractableHelpText = FString::Printf(TEXT("%s: E To Pick Up"), *ItemName);
}

void APickUp::Interact_Implementation()
{
	AMyCharacter* Character = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (Character->AddItemToInventory(this))
	{
		OnPickup();
	}
	

}

void APickUp::Use_Implementation()
{
	GLog->Log("Use() Base Function YOU SHOULD NOT BE SEEING THIS");
}

void APickUp::OnPickup()
{
	InteractableMesh->SetVisibility(false);
	InteractableMesh->SetSimulatePhysics(false);
	InteractableMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}
