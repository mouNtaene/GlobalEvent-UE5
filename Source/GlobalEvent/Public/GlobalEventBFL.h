// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GlobalEventSubsystem.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GlobalEventBFL.generated.h"


UCLASS()
class GLOBALEVENT_API UGlobalEventBFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/* Supported: bool, int, float(double), name, string, byte(convert enum to byte or int), struct, object  */
	UFUNCTION(BlueprintPure, CustomThunk, Category = "GlobalEvent|Conversion", meta=(CustomStructureParam = "Data", AutoCreateRefTerm = "Data"))
			static FGEWildcardProperty ConvertToWildcard(TFieldPath<FProperty> Data);

	DECLARE_FUNCTION(execConvertToWildcard)
	{
		FGEWildcardProperty OutProp;
		Stack.MostRecentProperty = nullptr;
		Stack.StepCompiledIn<FProperty>(NULL);
		//// Steps into the stack, walking to the next property in it
		//Stack.Step(Stack.Object, NULL);

		// Grab the last property found when we walked the stack
		// This does not contains the property value, only its type information
		FProperty* Property = CastField<FProperty>(Stack.MostRecentProperty);

		if (!Property)
		{
			Stack.bAbortingExecution = true;
			return;
		}
		// Grab the base address where the struct actually stores its data
		// This is where the property value is truly stored
		void* PropPtr = Stack.MostRecentPropertyAddress;

		// Copy Propetry values to wildcard struct 
		OutProp.Property = Property;
		OutProp.PropertyPtr = PropPtr;

		// We need this to wrap up the stack
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FGEWildcardProperty*)RESULT_PARAM = OutProp; //output
		P_NATIVE_END;
		
	}

	/** Convert wildcard property into a literal bool */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Bool (Wildcard Property)"), Category = "GlobalEvent|Conversion")
		static bool WildcardToBool(const FGEWildcardProperty& InProp, bool& OutBool);

	/** Convert wildcard property into a literal int */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Integer (Wildcard Property)"), Category = "GlobalEvent|Conversion")
		static bool WildcardToInt(const FGEWildcardProperty& InProp, int32& OutInt);

	/** Convert wildcard property into a literal float (may be double with conversion to float) */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Float (Wildcard Property)"), Category = "GlobalEvent|Conversion")
		static bool WildcardToFloat(const FGEWildcardProperty& InProp, float& OutFloat);
	
	/** Convert wildcard property into a literal double */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Double (Wildcard Property)"), Category = "GlobalEvent|Conversion")
		static bool WildcardToDouble(const FGEWildcardProperty& InProp, double& OutDouble);

	/** Convert wildcard property into a literal name */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Name (Wildcard Property)"), Category = "GlobalEvent|Conversion")
		static bool WildcardToName(const FGEWildcardProperty& InProp, FName& OutName);

	/** Convert wildcard property into a vector */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Vector (Wildcard Property)"), Category = "GlobalEvent|Conversion")
		static bool WildcardToVector(const FGEWildcardProperty& InProp, FVector& OutVector);

	/** Convert wildcard property into a byte */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Byte (Wildcard Property)"), Category = "GlobalEvent|Conversion")
		static bool WildcardToByte(const FGEWildcardProperty& InProp, uint8& OutByte);

	/** Convert wildcard property into a string */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To String (Wildcard Property)"), Category = "GlobalEvent|Conversion")
		static bool WildcardToString(const FGEWildcardProperty& InProp, FString& OutString);

	/** Convert wildcard property into a Object */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Object (Wildcard Property)"), Category = "GlobalEvent|Conversion")
		static bool WildcardToObject(const FGEWildcardProperty& InProp, UObject*& OutObject);

	/** Convert wildcard property into any struct */
	UFUNCTION(BlueprintPure, CustomThunk, meta = (DisplayName = "To Struct (Wildcard Property)", CustomStructureParam = "OutStruct", AutoCreateRefTerm = "OutStruct"), Category = "GlobalEvent|Conversion")
		static bool WildcardToStruct(const FGEWildcardProperty& InProp, TFieldPath<FProperty>& OutStruct);

	/** Convert wildcard property into any array */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Array (Wildcard Property)", ArrayParm = "OutArray", ArrayTypeDependentParams = "OutArray"), Category = "GlobalEvent|Conversion")
		static bool WildcardToArray(const FGEWildcardProperty& InProp, TArray<UProperty*>& OutArray);


	DECLARE_FUNCTION(execWildcardToStruct)
	{
		Stack.MostRecentProperty = nullptr;
		FGEWildcardProperty InProp;
		FGEWildcardProperty OutProp;

		//Determine copy wildcard property variables
		Stack.StepCompiledIn<FStructProperty>(&InProp);

		Stack.Step(Stack.Object, NULL);
		FProperty* ParameterProp = CastField<FProperty>(Stack.MostRecentProperty);
		void* PropPtr = Stack.MostRecentPropertyAddress;

		OutProp.Property = ParameterProp;
		OutProp.PropertyPtr = PropPtr;

		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)RESULT_PARAM = Generic_WildcardToStruct(InProp, OutProp);
		P_NATIVE_END;

	}


private:
	static bool Generic_WildcardToStruct(const FGEWildcardProperty& InProp, FGEWildcardProperty& OutProp);
	
public:
	//	/* VARIABLES FROM OBJECT */

	///* Get Variables */

	///** Get  boolean value from object  */
	//UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Bool from Object"), Category = "GlobalEvent|Variables")
	//	static bool GetBoolByName(UObject* Target, FName VarName, bool& OutBool);

	///** Get float value from object  */
	//UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Float from Object"), Category = "GlobalEvent|Variables")
	//	static bool GetFloatByName(UObject* Target, FName VarName, float& OutFloat);

	///** Get integer value from object  */
	//UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Int from Object"), Category = "GlobalEvent|Variables")
	//	static bool GetIntByName(UObject* Target, FName VarName, int& OutInt);

	///** Get integer value from object */
	//UFUNCTION(BlueprintPure, meta = (DisplayName = "Check name in Object"), Category = "GlobalEvent|Variables")
	//	static bool CheckNameVarByName(UObject* Target, FName VarName);

	///** Get integer value from object  */
	//UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Vector from Object"), Category = "GlobalEvent|Variables")
	//	static bool GetVectorByName(UObject* Target, FName VarName, FVector& OutVector);

	///* Set Variables */

	



	UFUNCTION(BlueprintPure, CustomThunk, Category = "GlobalEvent|Variables", meta = (CustomStructureParam = "Value", AutoCreateRefTerm = "Value", DisplayName = "Get Variable By Name"))
		static bool GetVariableByName(UObject* Object, FName VariableName, int32& Value);

	// get property
	DECLARE_FUNCTION(execGetVariableByName)
	{
		P_GET_OBJECT(UObject, Object);
		P_GET_PROPERTY(FNameProperty, VariableName);

		Stack.StepCompiledIn<FStructProperty>(NULL);
		void* SrcPropertyAddr = Stack.MostRecentPropertyAddress;
		FProperty* SrcProperty = CastField<FProperty>(Stack.MostRecentProperty);
		if (!SrcProperty)
		{
			Stack.bAbortingExecution = true;
			return;
		}
		
		P_FINISH;

		P_NATIVE_BEGIN;
		*(bool*)RESULT_PARAM = Generic_AccessVariableByName(Object, VariableName, SrcPropertyAddr, SrcProperty,false);
		P_NATIVE_END;

		
	}

	// Get or set a UPROPERTY of UObject by property name
	static bool Generic_AccessVariableByName(UObject* OwnerObject, FName PropertyName, void* SrcPropertyAddr, FProperty* SrcProperty, bool bSetter);

	UFUNCTION(BlueprintCallable, CustomThunk, Category = "GlobalEvent|Variables", meta = (CustomStructureParam = "Value", AutoCreateRefTerm = "Value", DisplayName = "Set Variable By Name"))
		static bool SetVariableByName(UObject* Object, FName VariableName, const int32& Value);

	// set property
	DECLARE_FUNCTION(execSetVariableByName)
	{
		P_GET_OBJECT(UObject, Object);
		P_GET_PROPERTY(FNameProperty, VariableName);

		Stack.StepCompiledIn<FStructProperty>(NULL);
		void* SrcPropertyAddr = Stack.MostRecentPropertyAddress;
		FProperty* SrcProperty = CastField<FProperty>(Stack.MostRecentProperty);

		P_FINISH;

		P_NATIVE_BEGIN;
		*(bool*)RESULT_PARAM = Generic_AccessVariableByName(Object, VariableName, SrcPropertyAddr, SrcProperty,true);
		P_NATIVE_END;

	}

	UFUNCTION(BlueprintCallable, Category = "GlobalEvent|Variables", meta = (DisplayName = "Call Function By Name"))
		static bool CallFunctionByName(UObject* Object, FName VariableName);
	

	UFUNCTION(BlueprintCallable, CustomThunk, Category = "GlobalEvent|Variables", meta = (CustomStructureParam = "Value", AutoCreateRefTerm = "Value", DisplayName = "Call Function By Name With Params"))
		static bool CallFunctionByNameWithParams(UObject* Object, FName VariableName, const int32& Value);

	DECLARE_FUNCTION(execCallFunctionByNameWithParams)
	{
		P_GET_OBJECT(UObject, OwnerObject);
		P_GET_PROPERTY(FNameProperty, VariableName);

		Stack.StepCompiledIn<FStructProperty>(NULL);
		void* SrcPtr = Stack.MostRecentPropertyAddress;
		FProperty* SrcProperty = CastField<FProperty>(Stack.MostRecentProperty);

		P_FINISH;

		P_NATIVE_BEGIN;
		*(bool*)RESULT_PARAM = Generic_CallFunctionByNameWithParams(OwnerObject, VariableName, SrcProperty, SrcPtr);
		P_NATIVE_END;

	}

	static bool Generic_CallFunctionByNameWithParams(UObject* OwnerObject, FName PropertyName, FProperty* SrcProperty,void* SrcPtr);
};
