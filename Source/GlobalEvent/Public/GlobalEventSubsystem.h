// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GlobalEventSubsystem.generated.h"



USTRUCT(BlueprintType)
struct FGEWildcardProperty
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Global Event")
	TFieldPath<FProperty> Property;

	void* PropertyPtr;
};

/** Wildcard Delegate */
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnGlobalEventData, const FGEWildcardProperty&, WildcardProperty);

/** Multicast variant of Wildcard Delegate  */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGlobalEventDataMulti, const FGEWildcardProperty&, WildcardProperty);

/** Event Delegate  */
DECLARE_DYNAMIC_DELEGATE(FOnGlobalEvent);

/** Multicast Event Delegate  */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGlobalEventMulti);


UCLASS()
class GLOBALEVENT_API UGlobalEventSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
private:
	
	UPROPERTY()
		TMap<FName, FOnGlobalEventDataMulti> GlobalEventsByNameWithData;

	UPROPERTY()
		TMap<FName, FOnGlobalEventMulti> GlobalEventsByName;

public:
	
	/**
	* Call event with data. Data can be any single property (wrap arrays/maps etc in a struct or object)
	*/
	UFUNCTION(BlueprintCallable, Category = "EventSystem", meta = (HidePin = "Sender", DefaultToSelf = "Sender"))
		void CallGlobalEventByNameWithData(UObject* Sender,  FName EventName , FGEWildcardProperty Wildcard);
	/**
	* Just call the event with no additional data
	*/
	UFUNCTION(BlueprintCallable, Category = "EventSystem", meta = (HidePin = "Sender", DefaultToSelf = "Sender"))
		void CallGlobalEventByName(UObject* Sender, FName EventName);

	/* Bind new event with additional data.
	*/
	UFUNCTION(BlueprintCallable, Category = "EventSystem")
		void BindGlobalEventByNameWithData(FName EventName, const FOnGlobalEventData& Event);

	/* Bind new event without data. For example trigger some timeline 
	*/
	UFUNCTION(BlueprintCallable, Category = "EventSystem")
		void BindGlobalEventByName(FName EventName, const FOnGlobalEvent& Event);

	/* Unbind event with additional data. 
	*/
	UFUNCTION(BlueprintCallable, Category = "EventSystem")
		void UnBindGlobalEventByNameWithData(FName EventName, const FOnGlobalEventData& Event);

	UFUNCTION(BlueprintCallable, Category = "EventSystem")
		void UnBindGlobalEventByName(FName EventName, const FOnGlobalEvent& Event);


	/* Helper function for debug purpose, to get all current events without data.
	*/
	UFUNCTION(BlueprintPure, Category = "EventSystem|Debug")
		TArray<FName> GetAllGlobalEventNames();

	/* Helper function for debug purpose, to get all current events with additional data.
	*/
	UFUNCTION(BlueprintPure, Category = "EventSystem|Debug")
		TArray<FName> GetAllGlobalEventNamesWithData();

};
