// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomToolsLibrary.h"

#include "IDesktopPlatform.h"
#include "Misc/FileHelper.h"
#include "DesktopPlatformModule.h"

#include "Engine/Texture2D.h"
#include "Runtime/RenderCore/Public/RenderUtils.h"
#include "Runtime/ImageWrapper/Public/IImageWrapper.h"
#include "Runtime/ImageWrapper/Public/IImageWrapperModule.h"

#include "Misc/Paths.h"
#include "HAL/PlatformProcess.h"
#include "HAL/FileManager.h"
#include "Misc/FeedbackContext.h"
#include "Editor/UnrealEd/Public/Editor.h"


void UCustomToolsLibrary::LoadImagesToArray_Constructor()
{
    FString SelectedFolder;

    IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
    if (DesktopPlatform)
    {
        void* ParentWindowHandle = FSlateApplication::Get().GetActiveTopLevelWindow()->GetNativeWindow()->GetOSWindowHandle();
        
        // Set the default path if needed
        FString DefaultPath = FPaths::ProjectDir();
        
        // Open the folder dialog
        bool bFolderSelected = DesktopPlatform->OpenDirectoryDialog(
            ParentWindowHandle,
            TEXT("Select a folder"),
            DefaultPath,
            SelectedFolder
        );

        if (bFolderSelected)
        {
            // Log the selected folder path
            UE_LOG(LogTemp, Warning, TEXT("Selected folder: %s"), *SelectedFolder);

            // Define the image file extensions we want to load
            const TArray<FString> ImageExtensions = { TEXT("png"), TEXT("jpg"), TEXT("jpeg"), TEXT("bmp"), TEXT("tga") };

            // Get all files in the selected directory
            TArray<FString> FoundFiles;
            IFileManager& FileManager = IFileManager::Get();

            // Use wildcard "*" to search for all files
            FileManager.FindFiles(FoundFiles, *(SelectedFolder / TEXT("*")), true, false);

            // Log the number of files found
            UE_LOG(LogTemp, Warning, TEXT("Number of files found: %d"), FoundFiles.Num());

            for (const FString& FileName : FoundFiles)
            {
                UE_LOG(LogTemp, Warning, TEXT("Found file: %s"), *FileName);

                // Get the file extension
                FString FileExtension = FPaths::GetExtension(FileName).ToLower();

                // Check if the file is an image
                if (ImageExtensions.Contains(FileExtension))
                {
                    // Construct the full file path
                    FString FullFilePath = FPaths::Combine(SelectedFolder, FileName);
                    
                    // Load the texture from the file
                    UTexture2D* LoadedTexture = LoadTextureFromFile(FullFilePath);

                    UE_LOG(LogTemp, Warning, TEXT("Full file path: %s"), *FullFilePath);

                    if (LoadedTexture)
                    {
                        // Add the loaded texture to the output array
                        SkyboxImages.Add(LoadedTexture);
                        UE_LOG(LogTemp, Warning, TEXT("Loaded image: %s"), *LoadedTexture->GetName());
                    }
                    else
                    {
                        UE_LOG(LogTemp, Warning, TEXT("Failed to load image: %s"), *FullFilePath);
                    }
                }
                else
                {
                    UE_LOG(LogTemp, Warning, TEXT("Skipped non-image file: %s"), *FileName);
                }
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("No folder selected."));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("DesktopPlatform not available."));
    }
}

UTexture2D* UCustomToolsLibrary::LoadTextureFromFile(const FString& FilePath)
{
    // Load image data from file
    TArray<uint8> FileData;
    if (!FFileHelper::LoadFileToArray(FileData, *FilePath))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load image file: %s"), *FilePath);
        return nullptr;
    }

    // Create image wrapper
    IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
    EImageFormat ImageFormat = ImageWrapperModule.DetectImageFormat(FileData.GetData(), FileData.Num());
    TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(ImageFormat);

    if (!ImageWrapper.IsValid() || !ImageWrapper->SetCompressed(FileData.GetData(), FileData.Num()))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to initialize image wrapper for: %s"), *FilePath);
        return nullptr;
    }

    // Create a TArray to hold the raw image data
    TArray<uint8> RawData;

    // Extract raw image data
    if (!ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, RawData))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to get raw image data for: %s"), *FilePath);
        return nullptr;
    }

    // Create texture
    int32 Width = ImageWrapper->GetWidth();
    int32 Height = ImageWrapper->GetHeight();
    UTexture2D* Texture = UTexture2D::CreateTransient(Width, Height, PF_B8G8R8A8);

    if (!Texture)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create texture for: %s"), *FilePath);
        return nullptr;
    }

    // Copy data to texture
    void* TextureData = Texture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
    FMemory::Memcpy(TextureData, RawData.GetData(), RawData.Num());
    Texture->GetPlatformData()->Mips[0].BulkData.Unlock();

    // Update the texture resource
    Texture->UpdateResource();

    return Texture;
}