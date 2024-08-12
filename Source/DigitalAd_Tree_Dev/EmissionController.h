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


	// Functions
	UFUNCTION(CallinEditor, Category = "Emission Controller")
	void ApplyDynamicMaterial();

	UFUNCTION(CallinEditor, Category = "Emission Controller")
	void ResetDynamicMaterial();

	UFUNCTION(CallinEditor, Category = "Emission Controller")
	void IncreaseStaticEmissionParam_Timer();
	void IncreaseStaticEmissionParam();
	



private:
	// Functions
	UFUNCTION(CallinEditor, Category = "Emission Controller")
	void OwnerInit();

	// Properties
	UPROPERTY(VisibleAnywhere, Category = "Emission Controller")
	FString OwnerName = "";

	UPROPERTY(EditAnywhere, Category = "Emission Controller")
	UMaterialInstance* ParentMaterialInstance = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Emission Controller")
	UMaterialInstanceDynamic* DynamicMaterialInstance = nullptr;

	AActor* Owner = nullptr;
	FTimerHandle StaticEmissionTimerHandle;
	float StaticEmissionIntensity = 0;
	FName StaticEmissionParameterName = "Intensity";
		
};
