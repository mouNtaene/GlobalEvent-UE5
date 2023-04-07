// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalEventBFL.h"

bool UGlobalEventBFL::WildcardToBool(const FGEWildcardProperty& InProp, bool& OutBool)
{
	if (InProp.Property == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UGlobalEventBFL::WildcardToBool InProp is a nullptr"));
		return false;
	}

	FBoolProperty* Property = CastField<FBoolProperty>(InProp.Property.Get());
	if (Property)
	{
		OutBool = Property->GetPropertyValue(InProp.PropertyPtr);
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UGlobalEventBFL::WildcardToBool %s is not a bool."), *InProp.Property->GetName());
		return false;
	}
}

bool UGlobalEventBFL::WildcardToInt(const FGEWildcardProperty& InProp, int32& OutInt)
{
	if (InProp.Property == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UGlobalEventBFL::WildcardToInt InProp is a nullptr"));
		return false;
	}

	FIntProperty* Property = CastField<FIntProperty>(InProp.Property.Get());
	if (Property)
	{
		OutInt = Property->GetPropertyValue(InProp.PropertyPtr);
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UGlobalEventBFL::WildcardToInt %s is not a int."), *InProp.Property->GetName());
		return false;
	}
}

bool UGlobalEventBFL::WildcardToFloat(const FGEWildcardProperty& InProp, float& OutFloat)
{
	if (InProp.Property == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UGlobalEventBFL::WildcardToFloat InProp is a nullptr"));
		return false;
	}
	
	FFloatProperty* Property = CastField<FFloatProperty>(InProp.Property.Get());

	if (Property)
	{
		OutFloat = Property->GetPropertyValue(InProp.PropertyPtr);
		return true;
	}
	else
	{
		FDoubleProperty* DoubleProperty = CastField<FDoubleProperty>(InProp.Property.Get());
		if (DoubleProperty)
		{
			double OutDouble = DoubleProperty->GetPropertyValue(InProp.PropertyPtr);
			OutFloat = (float)OutDouble;
			return true;
		}
		else {
		UE_LOG(LogTemp, Warning, TEXT("UGlobalEventBFL::WildcardToFloat %s is not a float."), *InProp.Property->GetName());
		return false;
		}
	}
}

bool UGlobalEventBFL::WildcardToDouble(const FGEWildcardProperty& InProp, double& OutDouble)
{
	if (InProp.Property == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UGlobalEventBFL::WildcardToDouble InProp is a nullptr"));
		return false;
	}
	FDoubleProperty* Property = CastField<FDoubleProperty>(InProp.Property.Get());
	if (Property)
	{
		OutDouble = Property->GetPropertyValue(InProp.PropertyPtr);
		return true;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("UGlobalEventBFL::WildcardToDouble %s is not a double."), *InProp.Property->GetName());
		return false;
	}
}

bool UGlobalEventBFL::WildcardToName(const FGEWildcardProperty& InProp, FName& OutName)
{
	if (InProp.Property == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UGlobalEventBFL::WildCardToName InProp is a nullptr"));
		return false;
	}

	FNameProperty* Property = CastField<FNameProperty>(InProp.Property.Get());
	if (Property)
	{
		OutName = Property->GetPropertyValue(InProp.PropertyPtr);
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UGlobalEventBFL::WildCardToName %s is not an FName."), *InProp.Property->GetName());
		return false;
	}
}

bool UGlobalEventBFL::WildcardToVector(const FGEWildcardProperty& InProp, FVector& OutVector)
{
	if (InProp.Property == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UGlobalEventBFL::WildCardToVector InProp is a nullptr"));
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

bool UGlobalEventBFL::WildcardToByte(const FGEWildcardProperty& InProp, uint8& OutByte)
{
	if (InProp.Property == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UGlobalEventBFL::WildCardToByte InProp is a nullptr"));
		return false;
	}

	FByteProperty* Property = CastField<FByteProperty>(InProp.Property.Get());

	if (Property)
	{
		OutByte = Property->GetPropertyValue(InProp.PropertyPtr);
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UGlobalEventBFL::WildCardToByte %s is not an byte."), *InProp.Property->GetName());
		return false;

	}
}

bool UGlobalEventBFL::WildcardToString(const FGEWildcardProperty& InProp, FString& OutString)
{
	
	if (InProp.Property == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UGlobalEventBFL::WildCardToString InProp is a nullptr"));
		return false;
	}

	FStrProperty* Property = CastField<FStrProperty>(InProp.Property.Get());
	if (Property)
	{
		OutString = Property->GetPropertyValue(InProp.PropertyPtr);
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UGlobalEventBFL::WildCardToString %s is not an string."), *InProp.Property->GetName());
		return false;
	}
	
}

bool UGlobalEventBFL::WildcardToObject(const FGEWildcardProperty& InProp, UObject*& OutObject)
{
	if (InProp.Property == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UGlobalEventBFL::WildCardToObject InProp is a nullptr"));
		return false;
	}

	FObjectProperty* Property = CastField<FObjectProperty>(InProp.Property.Get());
	if (Property)
	{
		OutObject = Property->GetPropertyValue(InProp.PropertyPtr);
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UGlobalEventBFL::WildCardToObject %s is not an object."), *InProp.Property->GetName());
		return false;
	}
}

bool UGlobalEventBFL::WildcardToArray(const FGEWildcardProperty& InProp, TArray<UProperty*>& OutArray)
{
	if (InProp.Property == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UGlobalEventBFL::WildCardToArray InProp is a nullptr"));
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
		UE_LOG(LogTemp, Warning, TEXT("UGlobalEventBFL::HandlePropToStruct InProp or OutProp is a nullptr"));
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
		return false;
	}
}


//bool UGlobalEventBFL::GetBoolByName(UObject* Target, FName VarName, bool& OutBool)
//{
//	if (Target) //make sure Target was set in blueprints. 
//	{
//		FBoolProperty* Property = FindFProperty<FBoolProperty>(Target->GetClass(), VarName);  // try to find float property in Target named VarName
//		if (Property) //if we found variable
//		{
//			OutBool = Property->GetPropertyValue_InContainer(Target);
//			return true; // we can return
//		}
//	}
//	return false; // we haven't found variable return false
//}
//
//bool UGlobalEventBFL::GetFloatByName(UObject* Target, FName VarName, float& OutFloat)
//{
//	if (Target)
//	{
//		FFloatProperty* Property = FindFProperty<FFloatProperty>(Target->GetClass(), VarName);  // try to find float property in Target named VarName
//		if (Property)
//		{
//			OutFloat = Property->GetPropertyValue_InContainer(Target);
//			return true; // we can return
//		}
//		else
//		{
//			FDoubleProperty* DoubleProperty = FindFProperty<FDoubleProperty>(Target->GetClass(), VarName); //check double in case it's not float
//			if (DoubleProperty)
//			{
//				double OutDouble = DoubleProperty->GetPropertyValue_InContainer(Target);
//				OutFloat = (float)OutDouble;
//				return true;
//			}
//			else
//			{
//				return false;
//			}
//		}
//	}
//	return false;
//}
//
//bool UGlobalEventBFL::GetIntByName(UObject* Target, FName VarName, int& OutInt)
//{
//	if (Target)
//	{
//		FIntProperty* Property = FindFProperty<FIntProperty>(Target->GetClass(), VarName);  // try to find float property in Target named VarName
//		if (Property)
//		{
//			OutInt = Property->GetPropertyValue_InContainer(Target);
//			return true; // we can return
//		}
//	}
//	return false;
//}
//
//bool UGlobalEventBFL::CheckNameVarByName(UObject* Target, FName VarName)
//{
//	if (Target)
//	{
//		FNameProperty* Property = FindFProperty<FNameProperty>(Target->GetClass(), VarName);  // try to find float property in Target named VarName
//		if (Property)
//		{
//			return true; // we can return
//		}
//	}
//
//	return false;
//}
//
//bool UGlobalEventBFL::GetVectorByName(UObject* Target, FName VarName, FVector& OutVector)
//{
//	if (Target)
//	{
//		FStructProperty* Property = FindFProperty<FStructProperty>(Target->GetClass(), VarName); 
//
//		if (Property && Property->Struct == TBaseStructure<FVector>::Get())
//		{
//			void* StructAddress = Property->ContainerPtrToValuePtr<void>(Target);
//			if (StructAddress)
//			{
//				Property->CopyCompleteValue(&OutVector, StructAddress);
//				return true; // we can return
//			}
//		}
//	}
//	return false;
//}
//
//bool UGlobalEventBFL::SetBoolByName(UObject* Target, FName VarName, bool NewValue, bool& OutBool)
//{
//	
//	if (Target) 
//	{
//		FBoolProperty* Property = FindFProperty<FBoolProperty>(Target->GetClass(), VarName);
//		if (Property) 
//		{
//			Property->SetPropertyValue_InContainer(Target,NewValue);
//			OutBool = Property->GetPropertyValue_InContainer(Target); // sanity check i guess
//			return true; 
//		}
//	}
//	return false; 
//
//}


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
		UClass* OwnerClass = Object->GetClass();
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
		UClass* OwnerClass = OwnerObject->GetClass();
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





