#pragma once

#include "UObject/Object.h"
#include "UObject/ObjectMacros.h"
#include "UGeodesicTestProjectObject.generated.h"

UCLASS()
class UGeodesicTestProjectObject : public UObject
{
	//TODO: should this be in private or public?
	GENERATED_BODY()

public:
	UPROPERTY()
	FText text;
	
	UPROPERTY()
	FName name;

	UPROPERTY()
	double value;
};
