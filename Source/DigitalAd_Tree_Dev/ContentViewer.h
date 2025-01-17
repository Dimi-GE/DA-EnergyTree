// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ContentViewer.generated.h"

class UMediaPlayer;
class UFileMediaSource;
class UWidgetComponent;
class UImage;
class ACineCameraActor;
class UUMG_ContentViewer;

UCLASS()
class DIGITALAD_TREE_DEV_API AContentViewer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AContentViewer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Properties
	UPROPERTY(EditAnywhere, Category = "Media")
    UMediaPlayer* MediaPlayer1;

	UPROPERTY(EditAnywhere, Category = "Media")
    UFileMediaSource* MediaSource1;

	UPROPERTY(VisibleAnywhere, Category = "Content Viewer Defaults")
	ACineCameraActor* ParentActor;

	UPROPERTY(EditAnywhere, Category = "Content Viewer Materials")
	UMaterialInstance* CentralDot;

	UPROPERTY(EditAnywhere, Category = "Content Viewer Materials")
	UMaterialInstance* SegmentedMotion;

	UPROPERTY(EditAnywhere, Category = "Content Viewer Materials")
	UMaterialInstance* Segmented;

	UPROPERTY(EditAnywhere, Category = "Content Viewer Materials")
	UMaterialInstance* OuterCircle;

	UPROPERTY(EditAnywhere, Category = "Content Viewer Materials")
	UMaterial* BackgroundImageMaterial;

	UPROPERTY(EditAnywhere, Category = "Content Viewer Materials")
	UMaterial* ContentImageMaterial;

	// UFUNCTION(CallInEditor, Category = "Content Viewer Defaults")
	void SetParentForSelf();

	UFUNCTION(CallInEditor, Category = "Content Viewer Defaults")
	void ResetReferences();

	// UFUNCTION(CallInEditor, Category = "Content Viewer Defaults")
	void DetachSelfFromParent();

	// UFUNCTION(CallInEditor, Category = "Media")
	void SetUpMediaPlayer();
};
