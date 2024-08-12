// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ParentActor.generated.h"

class UMediaPlayer;
class UFileMediaSource;

UCLASS()
class DIGITALAD_TREE_DEV_API AParentActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AParentActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Media")
    UMediaPlayer* MediaPlayer1;

	UPROPERTY(EditAnywhere, Category = "Media")
    UMediaPlayer* MediaPlayer2;

	UPROPERTY(EditAnywhere, Category = "Media")
    UFileMediaSource* MediaSource1;

	UPROPERTY(EditAnywhere, Category = "Media")
    UFileMediaSource* MediaSource2;

	UFUNCTION(CallInEditor, Category = "Media")
	void SetUpMediaPlayers();

};
