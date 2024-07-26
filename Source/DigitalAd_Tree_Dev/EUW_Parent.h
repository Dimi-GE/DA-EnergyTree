// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "EUW_Parent.generated.h"

/**
 * 
 */

class UStaticMesh;

UCLASS()
class DIGITALAD_TREE_DEV_API UEUW_Parent : public UEditorUtilityWidget
{
	GENERATED_BODY()
public:

    // The selected static mesh
    // UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SkyboxUtilityLibrary")
    UStaticMeshComponent* SelectedStaticMeshComponent;
	
	// UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SkyboxUtilityLibrary")
	UMaterialInstance* SkyboxMaterialInstance;
	UMaterialInstanceDynamic* SkyboxMaterialInstanceDynamic;

	UFUNCTION(BlueprintCallable, Category = "SkyboxUtilityLibrary")
	void EUWInitialization();

    // Function to pick a static mesh from the level
    UFUNCTION(BlueprintCallable, Category = "SkyboxUtilityLibrary")
    void PickStaticMeshFromLevel(FString &ActorName);

	UFUNCTION(BlueprintCallable, Category = "SkyboxUtilityLibrary")
	void LoadImagesToArray();

	UFUNCTION(BlueprintCallable, Category = "SkyboxUtilityLibrary")
	UTexture2D* ShowNextImage();

	UFUNCTION(BlueprintCallable, Category = "SkyboxUtilityLibrary")
	UTexture2D* ShowPreviousImage();

private:
	
	int32 SkyboxImagesLength;
	TArray<UTexture2D*> SkyboxImages;
	int32 CurrentImageIndex;

	TArray<UTexture2D*> LoadTexturesFromDirectory();
	UTexture2D* LoadTextureFromFile(const FString& FilePath);
	void AccessMaterialInstances();

};
