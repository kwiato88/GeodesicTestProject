#include "FGeodesicTestProjectObjectSpawner.h"
#include "Containers/Array.h"

namespace
{
UGeodesicTestProjectObject* BuildObject()
{
	UGeodesicTestProjectObject * obj = NewObject<UGeodesicTestProjectObject>();
	obj->text = FText::FromString("Hello Text");
	obj->name = FName("Hello Text");
	obj->value = 44.78;

	return obj;
}

void Serialize(UGeodesicTestProjectObject& object, TArray<uint8>& out)
{
	FMemoryWriter writer(out);
	object.Serialize(writer);
}

void Save(const TArray<TArray<uint8>>& objects, const FString& filePath)
{
	//TODO:
}
}

void FGeodesicTestProjectObjectSpawner::SpawnObject(uint32 numObjects)
{
	//TODO: UObjects don't need to be manually deleted, right?
	//https://docs.unrealengine.com/en-US/ProgrammingAndScripting/ProgrammingWithCPP/UnrealArchitecture/Objects/index.html
	objects.AddUninitialized(numObjects);
	for (uint32 i = 0; i < numObjects; ++i)
		objects[i] = BuildObject();
}

int32 FGeodesicTestProjectObjectSpawner::SaveObjectsToFile(const FString& filePath) const
{
	using Size = TArray<UGeodesicTestProjectObject*>::SizeType;

	TArray<TArray<uint8>> buff;
	buff.SetNum(objects.Num());
	for (Size i = 0; i < objects.Num(); ++i)
		Serialize(*objects[i], buff[i]);
	Save(buff, filePath);

	//TODO: what should be returned?
	return int32();
}
