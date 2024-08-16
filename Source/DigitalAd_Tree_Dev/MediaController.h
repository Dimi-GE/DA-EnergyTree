// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MediaController.generated.h"

class UMediaPlayer;
class UFileMediaSource;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DIGITALAD_TREE_DEV_API UMediaController : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMediaController();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, Category = "Media")
    UMediaPlayer* MediaPlayer1;

	UPROPERTY(EditAnywhere, Category = "Media")
    UMediaPlayer* MediaPlayer2;

	UPROPERTY(EditAnywhere, Category = "Media")
    UFileMediaSource* MediaSource1;

	UPROPERTY(EditAnywhere, Category = "Media")
    UFileMediaSource* MediaSource2;

	UPROPERTY(EditAnywhere, Category = "Media Defaults")
	int32 RenderAtSecond;

	UFUNCTION(CallInEditor, Category = "Media")
	void PlayPreparedMedia();

};
