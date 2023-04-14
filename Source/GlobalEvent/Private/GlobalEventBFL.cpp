// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalEventBFL.h"

template<typename FFieldType,typename T> 
bool GetWildCardValue(const FGEWildcardProperty& InProp, T& Value, const bool PruneWarning = false)
{
	if (InProp.Property == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UGlobalEventBFL::Wildcard Property is a nullptr")); 
		return false;
	}
	FFieldType* Property = CastField<FFieldType>(InProp.Property.Get());
	if (Property)
	{
		Value = Property->GetPropertyValue(InProp.PropertyPtr);
		return true;
	}
	else
	{
		if (!PruneWarning) {
			UE_LOG(LogTemp, Warning, TEXT("UGlobalEventBFL::Wildcard Property %s differ in type, connect right type!."), *InProp.Property->GetName());
		}
		return false;
	}
}


bool UGlobalEventBFL::WildcardToBool(const FGEWildcardProperty& InProp, bool& OutBool)
{	
	return GetWildCardValue<FBoolProperty>(InProp, OutBool);
}

bool UGlobalEventBFL::WildcardToInt(const FGEWildcardProperty& InProp, int32& OutInt)
{
	return GetWildCardValue<FIntProperty>(InProp, OutInt);
}

bool UGlobalEventBFL::WildcardToFloat(const FGEWildcardProperty& InProp, float& OutFloat)
{
	const bool IsFloat = GetWildCardValue<FFloatProperty>(InProp, OutFloat,true); // handle warnin TODO: Add Fname->FString conversion?
	if (IsFloat)
	{
		return true;
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("UGlobalEventBFL::WildcardToFloat %s is actually double."), *InProp.Property->GetName());  need to put warning after result, additional bool for nothing
		return (float)GetWildCardValue<FDoubleProperty>(InProp, OutFloat); //typecast to float..
	}
}

bool UGlobalEventBFL::WildcardToDouble(const FGEWildcardProperty& InProp, double& OutDouble)
{
	return GetWildCardValue<FDoubleProperty>(InProp, OutDouble);
}

bool UGlobalEventBFL::WildcardToName(const FGEWildcardProperty& InProp, FName& OutName)
{
	return GetWildCardValue<FNameProperty>(InProp, OutName);
}


bool UGlobalEventBFL::WildcardToByte(const FGEWildcardProperty& InProp, uint8& OutByte)
{
	return GetWildCardValue<FByteProperty>(InProp, OutByte);
}

bool UGlobalEventBFL::WildcardToString(const FGEWildcardProperty& InProp, FString& OutString)
{
	return GetWildCardValue<FStrProperty>(InProp, OutString);
}

bool UGlobalEventBFL::WildcardToObject(const FGEWildcardProperty& InProp, UObject*& OutObject)
{
	return GetWildCardValue<FObjectProperty>(InProp, OutObject);
}

bool UGlobalEventBFL::WildcardToVector(const FGEWildcardProperty& InProp, FVector& OutVector)
{
	if (InProp.Property == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UGlobalEventBFL::WildCardToVector Property is a nullptr"));
		return false;
	}

	FStructProperty* Property = CastField<FStructProperty>(InProp.Property.Get());

	if (Property && Property->Struct == TBaseStructure<FVector>::Get())
	{

		Property->CopyCompleteValue(&OutVector, InProp.PropertyPtr);
		return true;
	}
	return false;
}

bool UGlobalEventBFL::WildcardToArray(const FGEWildcardProperty& InProp, TArray<UProperty*>& OutArray)
{
	if (InProp.Property == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UGlobalEventBFL::WildCardToArray Property is a nullptr"));
		return false;
	}

	FArrayProperty* Property = CastField<FArrayProperty>(InProp.Property.Get());

	if (Property)
	{
		Property->CopyCompleteValue(&OutArray, InProp.PropertyPtr);
		return true; 
	}
	UE_LOG(LogTemp, Warning, TEXT("UGlobalEventBFL::WildCardToArray %s is not an array."), *InProp.Property->GetName());
	return false;
}

bool UGlobalEventBFL::Generic_WildcardToStruct(const FGEWildcardProperty& InProp, FGEWildcardProperty& OutProp)
{
	if (InProp.Property == nullptr || OutProp.Property == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UGlobalEventBFL::HandlePropToStruct InProperty or OutProperty is a nullptr"));
		return false;
	}

	if (InProp.Property->IsA<FStructProperty>() && OutProp.Property->IsA<FStructProperty>())
	{
		FStructProperty* InStructProp = CastField<FStructProperty>(InProp.Property.Get());
		FStructProperty* OutStructProp = CastField<FStructProperty>(OutProp.Property.Get());

		OutStructProp->CopyCompleteValue(OutProp.PropertyPtr, InProp.PropertyPtr);
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UGlobalEventBFL::HandlePropToStruct Structs are different types"));
		return false;
	}
}



/* Deffinitions to access variables and functions */

bool UGlobalEventBFL::Generic_AccessVariableByName(UObject* OwnerObject, FName PropertyName, void* SrcPropertyAddr, FProperty* SrcProperty, bool bSetter)
{
	if (OwnerObject)
	{
		FProperty* FoundProp = FindFProperty<FProperty>(OwnerObject->GetClass(), PropertyName);

		if (FoundProp && (FoundProp->SameType(SrcProperty)))
		{
			void* Dest = FoundProp->ContainerPtrToValuePtr<void>(OwnerObject);
			if (bSetter == true)
			{
				FoundProp->CopySingleValue(Dest, SrcPropertyAddr);
			}
			else
			{
				FoundProp->CopySingleValue(SrcPropertyAddr, Dest);
			}
			return true;
		}
	}
	return false;
}

bool UGlobalEventBFL::CallFunctionByName(UObject* Object, FName VariableName)
{
	if (Object)
	{
		const UClass* OwnerClass = Object->GetClass();
		if (OwnerClass)
		{
			UFunction* OwnerFunc = OwnerClass->FindFunctionByName(VariableName);
			if (OwnerFunc && OwnerFunc->NumParms == 0)
			{
				Object->ProcessEvent(OwnerFunc, nullptr);
				return true;
			}
		}
	}
	return false;
}

bool UGlobalEventBFL::Generic_CallFunctionByNameWithParams(UObject* OwnerObject, FName PropertyName, FProperty* SrcProperty, void* SrcPtr)
{
	if (OwnerObject)
	{
		const UClass* OwnerClass = OwnerObject->GetClass();
		if (OwnerClass)
		{
			UFunction* OwnerFunc = OwnerClass->FindFunctionByName(PropertyName);

			if (OwnerFunc)
			{
				if (OwnerFunc->HasAnyFunctionFlags(FUNC_Native))
				{
					OwnerObject->ProcessEvent(OwnerFunc, SrcPtr);
					return true;
				}

				if (OwnerFunc->NumParms == 1) 
				{
					bool CanExecute = false;
					for (TFieldIterator<FProperty> It(OwnerFunc); It; ++It) //loop properties to be sure we have valid param
					{
						if (It->PropertyFlags&(CPF_Parm) && SrcProperty->SameType(*It) /*&& !(It->PropertyFlags & (CPF_ReturnParm))*/) //check if variable is the same as target, param and not return param
						{
							CanExecute = true;
							break;
						}
					}

					if (CanExecute)
					{
						uint8* Parms = (uint8*)FMemory_Alloca_Aligned(OwnerFunc->ParmsSize, OwnerFunc->GetMinAlignment()); // copy from callfunctionwithargs
						FMemory::Memzero(Parms, OwnerFunc->ParmsSize);
						uint8* FuncBufferPtr = (uint8*)SrcPtr;
						//int Index = 0;
						for (TFieldIterator<FProperty> i(OwnerFunc); i; ++i)
						{
							FProperty* Prop = *i;
							//Index += 1;
							if (Prop->GetFName().ToString().StartsWith("__")) // one prop is for something else (idk for now)
							{
								continue;
							}

							void* PropBuffer = Prop->ContainerPtrToValuePtr<void*>(Parms);
							if (Prop->PropertyFlags & CPF_Parm) //check if it's a variable 
							{
								
								Prop->CopyCompleteValue(PropBuffer, FuncBufferPtr); // set new value
								FuncBufferPtr += Prop->GetSize();
						
							}

						}
						//UE_LOG(LogTemp, Warning, TEXT("Properties num = %d"),Index);

						OwnerObject->ProcessEvent(OwnerFunc, Parms); // call func

						for (TFieldIterator<FProperty> It(OwnerFunc); It && It->HasAnyPropertyFlags(CPF_Parm); ++It)
						{
							It->DestroyValue_InContainer(Parms);
						}
						return true;

					}
					
				}

			}
		}
	}
	return false;
}





