// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "PickUp.generated.h"

/**
 * 
 */
UCLASS()
class APickUp : public AInteractable
{
	GENERATED_BODY()

public:

	APickUp();
	virtual void BeginPlay() override;

	virtual void Interact_Implementation() override;

	UFUNCTION(BlueprintNativeEvent)
		void Use();

	virtual void Use_Implementation();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Properties")
		FString ItemName;

	UPROPERTY(EditAnywhere, Category = "Pickup Properties")
		int32 Value;
		
	UPROPERTY(EditAnywhere, Category = "Pickup Properties")
		UTexture2D* ItemThumb;

	void OnPickup();
	
};
