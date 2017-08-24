// Fill out your copyright notice in the Description page of Project Settings.

#include "HP1.h"
#include "MyCharacter.h"
#include "MyGameMode.h"
#include "Blueprint/UserWidget.h"

AMyGameMode::AMyGameMode()
{
//Set default HUD state
HUDState = EHUDState::HS_Ingame;

}
void AMyGameMode::BeginPlay()
{
	ApplyHUDChanges();
}
void AMyGameMode::ApplyHUDChanges()
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromParent();
	}

	switch (HUDState)
	{
	case EHUDState::HS_Ingame:
	{
		ApplyHUD(IngameHUDClass, false, false);
		break;

	}
	case EHUDState::HS_Inventory:
	{
		ApplyHUD(InventoryHUDClass, true, true);
		break;

	}
	case EHUDState::HS_Shop_General:
	{
		ApplyHUD(ShopHUDClass, true, true);
		break;

	}
	default:
	{
		ApplyHUD(IngameHUDClass, false, false);
		break;

	}
	}
}

uint8 AMyGameMode::GetHUDState()
{
	return HUDState;
}

void AMyGameMode::SetHUDState(uint8 NewState)
{
	HUDState = NewState;
	ApplyHUDChanges();
}

bool AMyGameMode::ApplyHUD(TSubclassOf<class UUserWidget> WidgetToApply, bool bShowMouseCursor, bool EnableClickEvents)
{
	AMyCharacter* Player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	APlayerController* Controller = GetWorld()->GetFirstPlayerController();

	if (WidgetToApply != nullptr)
	{
		Controller->bShowMouseCursor = bShowMouseCursor;
		Controller->bEnableClickEvents = EnableClickEvents;

		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetToApply);

		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
			return true;
		}
		else 
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}


