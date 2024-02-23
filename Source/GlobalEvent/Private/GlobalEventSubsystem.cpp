// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalEventSubsystem.h"


void UGlobalEventSubsystem::CallGlobalEventByNameWithData(UObject* Sender, FName EventName, FGEWildcardProperty Wildcard)
{
	if (!Sender)
	{
		UE_LOG(LogTemp, Warning, TEXT("UGlobalEventSybsystem is not initialized. Eventname = %s"), *EventName.ToString());
		return;
	}
	if (EventName.IsNone())
	{
		UE_LOG(LogTemp, Warning, TEXT("UGlobalEventSybsystem: Eventname is None!'"));
		return;
	}
	if (GlobalEventsByNameWithData.Contains(EventName))
	{
		if (Wildcard.Property == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("UGlobalEventSybsystem: %s wildcard is nullptr."), *Wildcard.Property->GetName());
		}
		else 
		{
			GlobalEventsByNameWithData.Find(EventName)->Broadcast(Wildcard);
		}
		
	}

}

void UGlobalEventSubsystem::CallGlobalEventByName(UObject* Sender, FName EventName)
{
	if (!Sender)
	{
		UE_LOG(LogTemp, Warning, TEXT("UGlobalEventSybsystem is not initialized. Eventname = %s"), *EventName.ToString());
		return;
	}
	if (EventName.IsNone())
	{
		UE_LOG(LogTemp, Warning, TEXT("UGlobalEventSybsystem: Eventname is None!'"));
		return;
	}
	if (GlobalEventsByName.Contains(EventName))
	{
		GlobalEventsByName.Find(EventName)->Broadcast();
	}
}

void UGlobalEventSubsystem::BindGlobalEventByNameWithData(FName EventName, const FOnGlobalEventData& Event)
{
	if (EventName.IsNone())
	{
		UE_LOG(LogTemp, Warning, TEXT("UGlobalEventSybsystem: Eventname is None."))
			return;
	}
	GlobalEventsByNameWithData.FindOrAdd(EventName).AddUnique(Event);

}

void UGlobalEventSubsystem::BindGlobalEventByName(FName EventName, const FOnGlobalEvent& Event)
{
	if (EventName.IsNone())
	{
		UE_LOG(LogTemp, Warning, TEXT("UGlobalEventSybsystem: Eventname is None."))
		return;
	}
	GlobalEventsByName.FindOrAdd(EventName).AddUnique(Event);
	
}

void UGlobalEventSubsystem::UnBindGlobalEventByNameWithData(FName EventName, const FOnGlobalEventData& Event)
{
	if (EventName.IsNone())
	{
		UE_LOG(LogTemp, Warning, TEXT("UGlobalEventSybsystem: Eventname is None."))
			return;
	}
	if (GlobalEventsByNameWithData.Contains(EventName))
	{
		GlobalEventsByNameWithData.Find(EventName)->Remove(Event);
	}
}

void UGlobalEventSubsystem::UnBindGlobalEventByName(FName EventName, const FOnGlobalEvent& Event)
{
	if (EventName.IsNone())
	{
		UE_LOG(LogTemp, Warning, TEXT("UGlobalEventSybsystem: Eventname is None."))
			return;
	}
	if (GlobalEventsByName.Contains(EventName))
	{
		GlobalEventsByName.Find(EventName)->Remove(Event);
		/*TODO: Delete from map if delegates = 0, save perf on useless broadcast in this case*/
	}
}

TArray<FName> UGlobalEventSubsystem::GetAllGlobalEventNames()
{
	TArray<FName> Events;
#if WITH_EDITOR
	GlobalEventsByName.GenerateKeyArray(Events);
	return Events;
#endif
	return Events;
}

TArray<FName> UGlobalEventSubsystem::GetAllGlobalEventNamesWithData()
{
	TArray<FName> Events;
#if WITH_EDITOR
	GlobalEventsByNameWithData.GenerateKeyArray(Events);
#endif
	return Events;
}

