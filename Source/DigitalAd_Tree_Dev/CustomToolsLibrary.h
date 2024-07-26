// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CustomToolsLibrary.generated.h"

/**
 * 
 */

class IDesktopPlatform;
class UTexture2D;

UCLASS()
class DIGITALAD_TREE_DEV_API UCustomToolsLibrary : public UObject
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadOnly, Category = "SkyboxEditorLibrary")
	TArray<UTexture2D*> SkyboxImages;

	UFUNCTION(BlueprintCallable, Category = "SkyboxEditorLibrary")
	void LoadImagesToArray_Constructor();


private:

	UTexture2D* LoadTextureFromFile(const FString& FilePath);


};