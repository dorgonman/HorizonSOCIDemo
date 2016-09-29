// Fill out your copyright notice in the Description page of Project Settings.

#include "HorizonSOCIDemo.h"
#include "HorizonSOCIDemoGameModeBase.h"

#include "soci/soci.h"
#include "soci/sqlite3/soci-sqlite3.h"

static FORCEINLINE void CreateDirectoryRecursively(FString FolderToMake)
{
	//FolderToMake is not const so split can be used, and does not damage input

	//Loop Proteciton
	const int32 MAX_LOOP_ITR = 3000; //limit of 3000 directories in the structure

									 // Normalize all / and \ to TEXT("/") and remove any trailing TEXT("/") 
									 //if the character before that is not a TEXT("/") or a colon
	FPaths::NormalizeDirectoryName(FolderToMake);

	//Normalize removes the last "/", but my algorithm wants it
	FolderToMake += "/";

	FString Base;
	FString Left;
	FString Remaining;

	//Split off the Root
	FolderToMake.Split(TEXT("/"), &Base, &Remaining);
	Base += "/"; //add root text to Base

	int32 LoopItr = 0;
	while (Remaining != "" && LoopItr < MAX_LOOP_ITR)
	{
		Remaining.Split(TEXT("/"), &Left, &Remaining);

		//Add to the Base
		Base += Left + FString("/"); //add left and split text to Base

									 //Create Incremental Directory Structure!
		FPlatformFileManager::Get().GetPlatformFile().CreateDirectory(*Base);

		LoopItr++;
	}
}
AHorizonSOCIDemoGameModeBase::AHorizonSOCIDemoGameModeBase() {
	

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	//GameLogDir()
	FString folderPath = (FPaths::GamePersistentDownloadDir() + "/Horizon/");
	//FString folderPath = (FPaths::GameLogDir() + "/Horizon/");
	folderPath = FPaths::ConvertRelativePathToFull(folderPath);
	CreateDirectoryRecursively(folderPath);

	FString connectString = folderPath + FString("save.db");

	FString testFilePath = folderPath + FString("test.txt");
	IFileHandle* FileHandle = PlatformFile.OpenWrite(*testFilePath);
	if (FileHandle)
	{
		FString Guid = FString(
			TEXT("// This file is written to disk\n")
			TEXT("// GUID = "))
			+ FGuid::NewGuid().ToString();

		FileHandle->Write((const uint8*)TCHAR_TO_ANSI(*Guid), Guid.Len());

		delete FileHandle;
	}

	bool result = PlatformFile.CreateDirectory(*folderPath);
	UE_LOG(LogTemp, Log, TEXT("1FolderPath: %s"), *folderPath);
	const soci::backend_factory* backEnd = soci::factory_sqlite3();
	UE_LOG(LogTemp, Log, TEXT("2FolderPath: %s"), *folderPath);
	std::string test = std::string(TCHAR_TO_UTF8(*connectString));
	//soci::session sql(*backEnd, test);
	//soci::sqlite3
	UE_LOG(LogTemp, Log, TEXT("3FolderPath: %s"), *folderPath);
}