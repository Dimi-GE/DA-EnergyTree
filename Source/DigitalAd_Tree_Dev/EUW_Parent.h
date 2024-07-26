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

	UFUNCTION(BlueprintCallable, Category = "SkyboxUtilityLibrary")
	void FresnelExponentParameterControl(float Value);

	UFUNCTION(BlueprintCallable, Category = "SkyboxUtilityLibrary")
	void IntensityParameterControl(float Value);

	UFUNCTION(BlueprintCallable, Category = "SkyboxUtilityLibrary")
	void PowerParameterControl(float Value);
	
	UFUNCTION(BlueprintCallable, Category = "SkyboxUtilityLibrary")
	void PowerDefaultValue(float &Value);

	UFUNCTION(BlueprintCallable, Category = "SkyboxUtilityLibrary")
	void FresnelExponentDefaultValue(float &Value);

	UFUNCTION(BlueprintCallable, Category = "SkyboxUtilityLibrary")
	void IntensityDefaultValue(float &Value);

private:
	// Scrolling functionality
	int32 SkyboxImagesLength;
	TArray<UTexture2D*> SkyboxImages;
	int32 CurrentImageIndex;

	// Material instance dynamic assignment functionality
    UStaticMeshComponent* SelectedStaticMeshComponent;
	UMaterialInstance* SkyboxMaterialInstance;
	UMaterialInstanceDynamic* SkyboxMaterialInstanceDynamic;

	// Dynamic material instance control
	TArray<UTexture2D*> LoadTexturesFromDirectory();
	UTexture2D* LoadTextureFromFile(const FString& FilePath);
	void AccessMaterialInstances();
};
