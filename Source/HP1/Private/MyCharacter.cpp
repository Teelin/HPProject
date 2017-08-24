// Fill out your copyright notice in the Description page of Project Settings.

#include "HP1.h"
#include "MyCharacter.h"
#include "Blueprint/UserWidget.h"

AMyCharacter::AMyCharacter()
{
	// Set Characters reach
	Reach = 250.f;
}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	InventoryArray.SetNum(InventorySize);
	CurrentInteractable = nullptr;
}

FString AMyCharacter::GetItemName(int32 Slot)
{
	if (InventoryArray[Slot] != NULL)
	{
		return InventoryArray[Slot]->ItemName;
	}
	else return FString("None");
}

void AMyCharacter::UseItem(int32 Slot)
{
	if (InventoryArray[Slot] != NULL)
	{
		InventoryArray[Slot]->Use_Implementation();
		InventoryArray[Slot] = NULL;
	}	
}

void AMyCharacter::DropItem(int32 Slot)
{
	//TODO Set up function to drop item
}

void AMyCharacter::ResizeInventory()
{
	// TODO set up a check if inventory has too many items to shrink??
	InventoryArray.SetNum(InventorySize);
}

void AMyCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &AMyCharacter::Inventory);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMyCharacter::Interact);

}

void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckInteractable();
}

void AMyCharacter::UpdateGold(int32 Amount)
{
	Gold = Gold + Amount;
}

bool AMyCharacter::AddItemToInventory(APickUp * Item)
{
	if (Item != NULL)
	{
		const int32 AvailableSlot = InventoryArray.Find(nullptr);
		if (AvailableSlot != INDEX_NONE)
		{
			InventoryArray[AvailableSlot] = Item;
			return true;
		}
		else
		{
			//TODO Add as a widget message (POPUP)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("You cant carry any more Items!"));
			return false;
		}
	}
	else return false;
}

UTexture2D * AMyCharacter::GetThumbnail(int32 Slot)
{
	if (InventoryArray[Slot] != NULL)
	{
		return InventoryArray[Slot]->ItemThumb;
	}
	else return nullptr;
}

void AMyCharacter::Inventory()
{
	//TODO code to open inventory
}

void AMyCharacter::Interact()
{
	if (CurrentInteractable != nullptr)
	{
		CurrentInteractable->Interact_Implementation();
	}
}

void AMyCharacter::CheckInteractable()
{
	/*
	// Get start and end trace from camera 
	AHP1Character *MyChar = Cast<AHP1Character>(UGameplayStatics::GetPlayerCharacter(this, 0));
	FVector StartTrace = MyChar->GetFollowCamera()->GetComponentLocation();
	FVector EndTrace = (MyChar->GetFollowCamera()->GetForwardVector() * Reach) + StartTrace;
	*/
	
	// Get start and end trace from player
	APawn *Myplayer = Cast<APawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	AMyCharacter *MyChar = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	FVector StartTrace = Myplayer->GetActorLocation();
	FVector EndTrace = (MyChar->GetFollowCamera()->GetForwardVector() * Reach) + StartTrace;
	
	// Set Hitresult out param
	FHitResult HitResult;

	//set up collison query to ignore the player
	FCollisionQueryParams CQP;
	CQP.AddIgnoredActor(this);

	// line trace into world looking for interactable objects
	GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_WorldDynamic, CQP);

	//Gets actor that is hit with linetrace
	AInteractable* PotentialInteractable = Cast<AInteractable>(HitResult.GetActor());

	//Check if hitresult is an interactable object
	if (PotentialInteractable == NULL)
	{
		HelpText = FString("");
		CurrentInteractable = nullptr;
		return;

	}
	else
	{
		CurrentInteractable = PotentialInteractable;
		HelpText = CurrentInteractable->InteractableHelpText;
		if (wPickupText) // Check if the Asset is assigned in the blueprint.
		{
			ItemWidget = CreateWidget<UUserWidget>(GetWorld(), wPickupText);
			if (ItemWidget)
			{
				ItemWidget->AddToViewport();
			}
		}
	}
	
}


