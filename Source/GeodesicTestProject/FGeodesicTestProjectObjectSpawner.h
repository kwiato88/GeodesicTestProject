#pragma once

#include "CoreMinimal.h"
#include "UGeodesicTestProjectObject.h"

class FGeodesicTestProjectObjectSpawner : public TSharedFromThis<FGeodesicTestProjectObjectSpawner>
{
public:
	~FGeodesicTestProjectObjectSpawner();

	void SpawnObject(uint32 numObjects);
	int32 SaveObjectsToFile(const FString& filePath);

private:
	TArray<TArray<uint8>> SerializeObjects();

	TArray<UGeodesicTestProjectObject*> objects;
	TArray<FString> savedFilesPaths;
};
