// Fill out your copyright notice in the Description page of Project Settings.

#include "HP1.h"
#include "Interactable.h"


// Sets default values
AInteractable::AInteractable()
{
 	
	InteractableHelpText = FString("Press 'E' to Interact with Item");

}

// Called when the game starts or when spawned
void AInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}


void AInteractable::Interact_Implementation()
{
	GLog->Log("Interact base class: Interact() YOU SHOULD NOT BE SEEING THIS");
}

