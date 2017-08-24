// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HP1Character.h"
#include "Interactable.h"
#include "PickUp.h"
#include "MyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AMyCharacter : public AHP1Character
{
	GENERATED_BODY()

	AMyCharacter();

	virtual void BeginPlay() override;
public:

	// Reference UMG Asset in the Editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<class UUserWidget> wPickupText;

	// Variable to hold the widget After Creating it.
	UUserWidget* ItemWidget;

	virtual void Tick(float DeltaTime) override;

	// Players Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
		FString HelpText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
		int32 Gold;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
		int32 InventorySize;
	

	UFUNCTION(BlueprintCallable, Category = "Inventory Functions")
		void UpdateGold(int32 Amount);
	UFUNCTION(BlueprintPure, Category = "Inventory Functions")
		bool AddItemToInventory(APickUp* Item);
	UFUNCTION(BlueprintPure, Category = "Inventory Functions")
		UTexture2D* GetThumbnail(int32 Slot);
	UFUNCTION(BlueprintPure, Category = "Inventory Functions")
		FString GetItemName(int32 Slot);
	UFUNCTION(BlueprintCallable, Category = "Inventory Functions")
		void UseItem(int32 Slot);
	UFUNCTION(BlueprintCallable, Category = "Inventory Functions")
		void DropItem(int32 Slot);
	UFUNCTION(BlueprintCallable, Category = "Inventory Functions")
		void ResizeInventory();

	// the interable the player is looking at
	UPROPERTY(BlueprintReadWrite)
		AInteractable* CurrentInteractable;

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:

	UPROPERTY(EditAnywhere, Category = "Character Settings")
		float Reach;

	// toggles the inventory on and of
	void Inventory();

	//interacts with interactable if there is one
	void Interact();

	// check if object is ineractable
	void CheckInteractable();

	// Create Inventory Array
	UPROPERTY(EditAnywhere)
		TArray<APickUp*> InventoryArray;

	
};
