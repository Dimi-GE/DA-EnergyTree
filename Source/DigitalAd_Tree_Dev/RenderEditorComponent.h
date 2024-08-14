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

    // UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RenderEditor")
    // FTransform CameraTransform;

    UPROPERTY()
    AActor* CameraActor;

	UPROPERTY(VisibleAnywhere)
	AActor* Owner;

	// UPROPERTY()
	FVector StartPosition;

	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RenderEditorTransforms")
	int32 CurrentPositionIndex;

	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RenderEditorTransforms")
	int32 CurrentRenderOrder;

	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RenderEditorTransforms")
	int32 CameraPathLength;

	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RenderEditor")
	// FVector EndPosition;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RenderEditorTransforms")
	FVector CurrentPosition;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RenderEditorTransforms")
	TArray<FVector> CameraPath;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RenderEditorTransforms")
	float Distance = 0;

	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RenderEditor")
	// float TargetDistance;

	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RenderEditor")
	// float StepSize = 0;
	
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RenderEditor")
	// float TargetIntensity = 0;

    // Timer handle for incrementing
    FTimerHandle IncrementTimerHandle;
	FTimerHandle CurrentPositionTimerHandle;

	// UFUNCTION(CallInEditor, Category = "RenderEditorTransforms")
	void TrackCurrentPosition_Timer();

	// UFUNCTION(CallInEditor, Category = "RenderEditorTransforms")
	void OwnerInit();


	// UFUNCTION(CallInEditor, Category = "RenderEditorTransforms")
	void RE_InvokeEmissionController();

	void RE_CalculateDistance();
	void PlayMedia();

};
