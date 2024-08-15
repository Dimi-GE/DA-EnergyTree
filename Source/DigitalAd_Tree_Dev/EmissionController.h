// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EmissionController.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DIGITALAD_TREE_DEV_API UEmissionController : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEmissionController();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Properties
	UPROPERTY(EditAnywhere, Category = "Emission Controller Defaults")
	int32 RenderOrder;

	UPROPERTY(EditAnywhere, Category = "Emission Controller Defaults")
	int32 RenderAtSecond;

	// Functions
	UFUNCTION(CallinEditor, Category = "Dynamic Emission Control")
	void ApplyDynamicMaterial();

	UFUNCTION(CallinEditor, Category = "Dynamic Emission Control")
	void ResetDynamicMaterial();

	// UFUNCTION(CallinEditor, Category = "Emission Controller")
	// void DEPR_IncreaseStaticEmissionParam_Timer(const float& StepSize, const float& TargetIntensity);

	UFUNCTION(CallinEditor, Category = "Dynamic Emission Control")
	void IncreaseEmissionParamDynamic();


private:
	// Functions
	UFUNCTION(CallinEditor, Category = "Emission Controller Defaults")
	void OwnerInit();

	// Properties
	// UPROPERTY(VisibleAnywhere, Category = "Emission Controller")
	// FString OwnerName = "";

	UPROPERTY(EditAnywhere, Category = "Dynamic Emission Control")
	float ControllerStepSize;

	UPROPERTY(EditAnywhere, Category = "Dynamic Emission Control")
	float ControllerTargetIntensity;

	UPROPERTY(EditAnywhere, Category = "Emission Controller Defaults")
	UMaterialInstance* ParentMaterialInstance = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Dynamic Emission Control")
	UMaterialInstanceDynamic* DynamicMaterialInstance = nullptr;

	AActor* Owner = nullptr;
	FTimerHandle StaticEmissionTimerHandle;
	float StaticEmissionIntensity = 0;
	FName StaticEmissionParameterName = "Intensity";
		
};
