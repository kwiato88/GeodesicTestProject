#pragma once

#include "CoreMinimal.h"
#include "UGeodesicTestProjectObject.h"

class FGeodesicTestProjectObjectSpawner : public TSharedFromThis<FGeodesicTestProjectObjectSpawner>
{
public:
	void SpawnObject(uint32 numObjects);
	int32 SaveObjectsToFile(const FString& filePath) const;

private:
	UGeodesicTestProjectObject* BuildObject() const;

	TArray<UGeodesicTestProjectObject*> objects;
};
