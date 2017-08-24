// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HP1GameMode.h"
#include "MyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class HP1_API AMyGameMode : public AHP1GameMode
{
	GENERATED_BODY()


		virtual void BeginPlay() override;
public:
	AMyGameMode();

	enum EHUDState : uint8
	{
		HS_Ingame,
		HS_Inventory,
		HS_Shop_General
	};

	void ApplyHUDChanges();

	uint8 GetHUDState();

	UFUNCTION(BlueprintCallable, Category = "HUD Functions")
		void SetHUDState(uint8 NewState);

	bool ApplyHUD(TSubclassOf<class UUserWidget> WidgetToApply, bool bShowMouseCursor, bool EnableClickEvents);

protected:

	uint8 HUDState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUDWidgets", Meta = (BlueprintProtected = "true"))
		TSubclassOf<class UUserWidget> IngameHUDClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUDWidgets", Meta = (BlueprintProtected = "true"))
		TSubclassOf<class UUserWidget> InventoryHUDClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUDWidgets", Meta = (BlueprintProtected = "true"))
		TSubclassOf<class UUserWidget> ShopHUDClass;

	UPROPERTY()
		class UUserWidget* CurrentWidget;
};
