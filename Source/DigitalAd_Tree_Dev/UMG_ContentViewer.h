// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UMG_ContentViewer.generated.h"

class UCanvasPanel;
class UImage;

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
};
