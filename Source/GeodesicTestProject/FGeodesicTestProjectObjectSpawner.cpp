#include "FGeodesicTestProjectObjectSpawner.h"
#include "Containers/Array.h"
#include "HAL/FileManager.h"

namespace
{
UGeodesicTestProjectObject* BuildObject()
{
	UGeodesicTestProjectObject* obj = NewObject<UGeodesicTestProjectObject>();
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

void Save(TArray<TArray<uint8>>& objects, const FString& filePath)
{
	//https://docs.unrealengine.com/en-US/API/Runtime/Core/HAL/IFileManager/index.html
	//does file need to exist? does is throw exceptions? how to handle errors?
	TUniquePtr<FArchive> writer(IFileManager::Get().CreateFileWriter(*filePath));
	if (!writer)
		return;

	for (auto& object : objects)
		writer->Serialize(object.GetData(), object.Num());
}
}

FGeodesicTestProjectObjectSpawner::~FGeodesicTestProjectObjectSpawner()
{
	for(const auto& path : savedFilesPaths)
		IFileManager::Get().Delete(*path);
}

void FGeodesicTestProjectObjectSpawner::SpawnObject(uint32 numObjects)
{
	//TODO: UObjects don't need to be manually deleted, right?
	//https://docs.unrealengine.com/en-US/ProgrammingAndScripting/ProgrammingWithCPP/UnrealArchitecture/Objects/index.html
	//TODO: should delte objects in array or just add new to the end?
	using Size = TArray<UGeodesicTestProjectObject*>::SizeType;
	Size oldNumberOfObjects = objects.AddUninitialized(numObjects);
	for (Size i = oldNumberOfObjects; i < objects.Num(); ++i)
		objects[i] = BuildObject();
}

TArray<TArray<uint8>> FGeodesicTestProjectObjectSpawner::SerializeObjects()
{
	using Size = TArray<UGeodesicTestProjectObject*>::SizeType;
	TArray<TArray<uint8>> buff;
	buff.SetNum(objects.Num());
	for (Size i = 0; i < objects.Num(); ++i)
		Serialize(*objects[i], buff[i]);
	return buff;
}

int32 FGeodesicTestProjectObjectSpawner::SaveObjectsToFile(const FString& filePath)
{
	savedFilesPaths.AddUnique(filePath);
	TArray<TArray<uint8>> buff(SerializeObjects());
	Save(buff, filePath);

	//TODO: what should be returned?
	return 1;
}
