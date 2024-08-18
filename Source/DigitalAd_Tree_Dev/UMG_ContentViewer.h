// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UMG_ContentViewer.generated.h"

class ContentViewer;
class UCanvasPanel;
class UImage;
class UMaterialInstanceDynamic;

/**
 * 
 */
UCLASS()
class DIGITALAD_TREE_DEV_API UUMG_ContentViewer : public UUserWidget
{
	GENERATED_BODY()

public:
    virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;


    UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
    UCanvasPanel* CanvasPanel;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UImage* GaugeTexture_CircledDot;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UImage* GaugeTexture_SegmentedMotion;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UImage* GaugeTexture_Segmented;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UImage* GaugeTexture_OuterCircle;

	// UPROPERTY(VisibleAnywhere, Category = "Content Viewer Materials Dynamic")
	UMaterialInstanceDynamic* SegmentedMotion_Dynamic;

	// UPROPERTY(VisibleAnywhere, Category = "Content Viewer Materials Dynamic")
	UMaterialInstanceDynamic* Segmented_Dynamic;

	// UPROPERTY(VisibleAnywhere, Category = "Content Viewer Materials Dynamic")
	UMaterialInstanceDynamic* OuterCircle_Dynamic;

	// Timer handlers
	FTimerHandle SegmentedMotionAnimationHandle;
	FTimerHandle SegmentedCirclePercentageHandle;
	FTimerHandle OuterCircleAnimationHandle;
	// Material instances default properties
	float SegmentedMotionPosition = 0.0f;
	float SegmentedCirclePosition = 0.0f;
	float SegmentedPercentage = 0.0f;
	float OuterCirclePosition = 0.0f;
	bool bIsIncreasing = true;

	// UFUNCTION(CallInEditor, Category = "Content Viewer Materials")
	void RE_SegmentedMotionCircleAnimation();

	// UFUNCTION(CallInEditor, Category = "Content Viewer Materials")
	void SegmentedCirclePercentageAnimation();

	// UFUNCTION(CallInEditor, Category = "Content Viewer Materials")
	void RE_OuterCircleAnimation();

	UFUNCTION(BlueprintCallable, Category = "Content Viewer")
	void DynamicMaterialInstances_Initialization(const AContentViewer* BPContentViewerRef, bool &bIsSucceed);

	UFUNCTION(BlueprintCallable, Category = "Content Viewer")
	void TimersInitialization();
};
