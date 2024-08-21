// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UMG_ContentViewer.generated.h"

class ContentViewer;
class UCanvasPanel;
class UOverlay;
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

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UImage* BackgroundImage;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UImage* ContentImage;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UOverlay* Gauge_Overlay;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UOverlay* Content_Overlay;

	// UPROPERTY(VisibleAnywhere, Category = "Content Viewer Materials Dynamic")
	UMaterialInstanceDynamic* SegmentedMotion_Dynamic;

	// UPROPERTY(VisibleAnywhere, Category = "Content Viewer Materials Dynamic")
	UMaterialInstanceDynamic* Segmented_Dynamic;

	// UPROPERTY(VisibleAnywhere, Category = "Content Viewer Materials Dynamic")
	UMaterialInstanceDynamic* OuterCircle_Dynamic;
	
	UMaterialInstanceDynamic* BackgroundImage_Dynamic;

	UMaterialInstanceDynamic* ContentImage_Dynamic;

	// Timer handlers
	FTimerHandle SegmentedMotionAnimationHandle;
	FTimerHandle SegmentedCirclePercentageHandle;
	FTimerHandle OuterCircleAnimationHandle;
	FTimerHandle BackgroundImageAnimationHandle;
	FTimerHandle ContentImageAnimationHandle;
	FTimerHandle CounterHandle;

	// Material instances default properties
	float BackgroundImageOpacity = 0.0f;
	float ContentImageOpacity = 0.0f;
	float SegmentedMotionPosition = 0.0f;
	float SegmentedCirclePosition = 0.0f;
	float SegmentedPercentage = 0.0f;
	float OuterCirclePosition = 0.0f;
	float CounterValue = 0;
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

	UFUNCTION(BlueprintCallable, Category = "Content Viewer")
	void MediaContent_Initialization(AContentViewer* BPContentViewerRef, bool &bIsSucceed);

	// UFUNCTION(BlueprintCallable, Category = "Content Viewer")
	void DI_BackgroundImage(UMaterial* ParentMaterial);
	void DI_ContentImage(UMaterial* ParentMaterial);

	UFUNCTION(BlueprintCallable, Category = "Content Viewer")
	void Counter();

	void BackgroundImageFadeAnim();
	void ContentImageFadeAnim();
};
