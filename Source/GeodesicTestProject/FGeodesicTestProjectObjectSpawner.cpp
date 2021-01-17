#include "FGeodesicTestProjectObjectSpawner.h"

UGeodesicTestProjectObject* FGeodesicTestProjectObjectSpawner::BuildObject() const
{
	UGeodesicTestProjectObject * obj = NewObject<UGeodesicTestProjectObject>();
	obj->text = FText::FromString("Hello Text");
	obj->name = FName("Hello Text");
	obj->value = 44.78;

	return obj;
}

void FGeodesicTestProjectObjectSpawner::SpawnObject(uint32 numObjects)
{
	//TODO: UObjects don't need to be manually delete, right?
	//https://docs.unrealengine.com/en-US/ProgrammingAndScripting/ProgrammingWithCPP/UnrealArchitecture/Objects/index.html
	objects.SetNum(numObjects);
	for (uint32 i = 0; i < numObjects; ++i)
		objects[i] = BuildObject();
}

int32 FGeodesicTestProjectObjectSpawner::SaveObjectsToFile(const FString& filePath) const
{
	//TODO:
	return int32();
}
