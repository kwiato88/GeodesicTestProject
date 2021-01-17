// Copyright Epic Games, Inc. All Rights Reserved.

#include "GeodesicTestProject.h"
#include "FGeodesicTestProjectObjectSpawner.h"
#include "Modules/ModuleManager.h"

class FGeodesicTestProject
	: public IModuleInterface
{
public:
	/**
	 * Called right after the module DLL has been loaded and the module object has been created
	 * Load dependent modules here, and they will be guaranteed to be available during ShutdownModule. ie:
	 *
	 * FModuleManager::Get().LoadModuleChecked(TEXT("HTTP"));
	 */
	virtual void StartupModule();

	/**
	 * Called before the module is unloaded, right before the module object is destroyed.
	 * During normal shutdown, this is called in reverse order that modules finish StartupModule().
	 * This means that, as long as a module references dependent modules in it's StartupModule(), it
	 * can safely reference those dependencies in ShutdownModule() as well.
	 */
	virtual void ShutdownModule();

private:
	TSharedPtr<FGeodesicTestProjectObjectSpawner> GeodesicTestProjectObjectSpawner;
};

void FGeodesicTestProject::StartupModule()
{
	UE_LOG(LogTemp, Warning, TEXT("FGeodesicTestProject::StartupModule"));

	// 1. Implement UGeodesicTestProjectObject class in the separate file
	// you can check how to implement UObject in engine source.
	// Any class which inherit from : public UObject
	// Keep in mind the GeodesicTestProject.h file should include the GeodesicTestProject.generated.h include
	// TODO: should it be UGeodesicTestProjectObject.h and UGeodesicTestProjectObject.generated.h ???

	// 2. Add multile properites to UGeodesicTestProjectObject class, 
	// please use UPROPERTY() macro, you can check at any class which inherit from UObject
	// Please add properites FText, FName, double
	// Exmaple in your class
	// UPROPERTY()
	// FText MyText;

	// 3. Implement class FGeodesicTestProjectObjectSpawner which inherits from TSharedFromThis<FGeodesicTestProjectObjectSpawner>
	// 3.1 Class should have a private variable of TArray<UGeodesicTestProjectObject*> Objects;
	// 3.2 It should have a function void SpawnObject(uint32 NumObjects); which is creates a new number of UGeodesicTestProjectObject with
	//	UGeodesicTestProjectObject* Obj = NewObject<UGeodesicTestProjectObject>() UE4 fucntion and store it in Objects Array
	// And initialize properties for Obj, For example 
	//		Obj->MyText = FText::FromString("Hello Text");
	//		Obj->MyName = FName("Hello Text");
	//		Obj->MyDouble = 44.78;
	// 3.3 Implement int32 SaveObjectsToFile(const FString& FilePath) - this function should serialize each of UGeodesicTestProjectObject from Objects to buffer 
	// and then store to combined arhive to file on hard drive
	// for exmaple:
	// TArray<TArray<uint8>> ObjectBuffer;
	// ObjectBuffer.AddUninitialized(Objects.Num())
	// for (int32 Index = 0; Index < Objects.Num(); ++Index)
	// {
	//		TArray<uint8>& Buffer = ObjectBuffer[Index];
	//		FMemoryWriter Writer(Buffer);
	//		UGeodesicTestProjectObject* CurrentObject = Objects[Index];
	//		CurrentObject->Serialize(Writer); // UE4 function for serialization;
	// }
	// // Then you need to figure out how to save ObjectBuffer to some file on harddrive

	// 4. Please Initialize FGeodesicTestProjectObjectSpawner with MakeShared<FGeodesicTestProjectObjectSpawner>() template function
	// 4.1 spawn 10 objects GeodesicTestProjectObjectSpawner->SpawnObject(10);
	// 4.2 Serialize the properties from UObjects and store to some file GeodesicTestProjectObjectSpawner->SaveObjectsToFile("D:\Marmot\MyFile.txt");

	GeodesicTestProjectObjectSpawner = MakeShared<FGeodesicTestProjectObjectSpawner>();
	GeodesicTestProjectObjectSpawner->SpawnObject(10);
	GeodesicTestProjectObjectSpawner->SaveObjectsToFile("C:\\Users\\pikwiatk\\GeodesicTestProjectExportFile.txt");
}

void FGeodesicTestProject::ShutdownModule()
{
	UE_LOG(LogTemp, Warning, TEXT("FGeodesicTestProject::ShutdownModule"));

	// 5. Release the FGeodesicTestProjectObjectSpawner

	// 6. Please delete file on harddrive on FGeodesicTestProjectObjectSpawner Destructor
}

IMPLEMENT_PRIMARY_GAME_MODULE(FGeodesicTestProject, GeodesicTestProject, "GeodesicTestProject" );
