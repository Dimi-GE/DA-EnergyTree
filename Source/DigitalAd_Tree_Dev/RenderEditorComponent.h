// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RenderEditorComponent.generated.h"

class UEmissionController;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DIGITALAD_TREE_DEV_API URenderEditorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URenderEditorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RenderEditor")
    FTransform CameraTransform;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RenderEditor")
    AActor* CameraActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RenderEditor")
	AActor* BuildingActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RenderEditor")
	float Var = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RenderEditor")
	FVector StartPosition;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RenderEditor")
	FVector EndPosition;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RenderEditor")
	FVector CurrentPosition;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RenderEditor")
	float Distance;

    // Timer handle for incrementing
    FTimerHandle IncrementTimerHandle;

	UFUNCTION(CallInEditor, Category = "RenderEditor")
	void StartIncrementing();

	UFUNCTION(CallInEditor, Category = "RenderEditor")
	void IncreaseEmission();

	void PlayMedia();
		
	void CameraCurrentTransform();
	void IncrementFloatValue();

	void CalculateDistance_Timer();
	void CalculateDistance();
};
