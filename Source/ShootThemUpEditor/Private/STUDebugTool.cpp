// Shoot Them Up Game. All Rights Reserved.


#include "STUDebugTool.h"

#include "imgui.h"
#include "ImGuiModule.h"
#include "Components/STUHealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/STUBaseCharacter.h"

// Sets default values
ASTUDebugTool::ASTUDebugTool()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASTUDebugTool::BeginPlay()
{
	Super::BeginPlay();

	FImGuiModule::Get().SetInputMode(false);
}

void ASTUDebugTool::UnrealImGuiText(FString Text)
{
	ImGui::Text(TCHAR_TO_ANSI(*Text));
}

// Called every frame
void ASTUDebugTool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	bool bIsInputMode = FImGuiModule::Get().IsInputMode();
	ASTUBaseCharacter* Character = Cast<ASTUBaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	USTUHealthComponent* HealthComponent = nullptr;
	if (Character)
	{
		HealthComponent = Character->GetComponentByClass<USTUHealthComponent>();
	}
	
	static bool bDebugMovement = false;
	static bool bDebugHealth = false;
	bool bIsDebuggingMovement = bDebugMovement && Character;
	bool bIsDebuggingHealth = bDebugHealth && Character;
	bool bIsRenderingAnyDebugOverlay = bIsDebuggingMovement || bIsDebuggingHealth;
	if (!bIsInputMode && bIsRenderingAnyDebugOverlay)
	{
		ImGui::SetNextWindowBgAlpha(0.35f);
		
		ImGui::Begin("Overlay", nullptr, ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoFocusOnAppearing |
			ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);
		ImGui::SetWindowPos(ImVec2(25.0f, 65.0f));
		ImGui::SetWindowCollapsed(bIsInputMode);
		if (Character && !bIsInputMode)
		{
			if (bDebugMovement)
			{
				UnrealImGuiText(TEXT("Velocity: ") + Character->GetVelocity().ToString());
				FString CurrentState = Character->IsRunning() ? TEXT("Running") : (
					Character->GetVelocity().IsZero() ? TEXT("Idle") : TEXT("Walking")
				);
				UnrealImGuiText(FString("State: ") + CurrentState );
				UnrealImGuiText(TEXT("Movement Direction: ") + FString::SanitizeFloat(Character->GetMovementDirection()));
			}
			if (bDebugHealth && HealthComponent)
			{
				UnrealImGuiText(TEXT("Health: ") + FString::SanitizeFloat(HealthComponent->GetHealth()));
				UnrealImGuiText( FString("Is Dead: ") + (HealthComponent->IsDead() ? TEXT("True") : TEXT("False")) );
			}
		}
		ImGui::End();
	}
	ImGui::Begin("STU Debug Tool (Shift+X)", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings);
	{
		ImGui::SetNextWindowBgAlpha(0.80f);
		ImGui::SetWindowCollapsed(!bIsInputMode);
		StyleImGui();
		ImGui::BeginTabBar("Main");
		ImGui::SetWindowPos(ImVec2(25, 45));
		ImGui::SetWindowSize(ImVec2(890, 390));
		if (ImGui::BeginTabItem("Character"))
		{
			FString CharacterName = "NO_ACTIVE_CHARACTER";
			if (Character)
			{
				CharacterName = Character->GetName();
			}
			
			UnrealImGuiText(TEXT("Name: ") + CharacterName);
			ImGui::Separator();

			ImGui::Checkbox("Debug Movement?", &bDebugMovement);
			ImGui::Checkbox("Debug Health?", &bDebugHealth);
			ImGui::Separator();
			
			if (Character)
			{
				static int DamageAmount = 25.0f;
				if (ImGui::Button("Take Damage"))
				{
					UGameplayStatics::ApplyDamage(Character, DamageAmount, nullptr, this, nullptr);
				}
				ImGui::SameLine();
				ImGui::SliderInt("", &DamageAmount, 0, 100);
			}
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
	ImGui::End();
}

void ASTUDebugTool::StyleImGui()
{
	ImGuiStyle* Style = &ImGui::GetStyle();
	
	ImVec4* Colors = Style->Colors;
	Colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	Colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	Colors[ImGuiCol_WindowBg]               = ImVec4(0.04f, 0.04f, 0.04f, 0.94f);
	Colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	Colors[ImGuiCol_PopupBg]                = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
	Colors[ImGuiCol_Border]                 = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	Colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	Colors[ImGuiCol_FrameBg]                = ImVec4(0.15f, 0.15f, 0.15f, 0.54f);
	Colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.48f, 0.26f, 0.98f, 0.40f);
	Colors[ImGuiCol_FrameBgActive]          = ImVec4(0.37f, 0.00f, 1.00f, 1.00f);
	Colors[ImGuiCol_TitleBg]                = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
	Colors[ImGuiCol_TitleBgActive]          = ImVec4(0.21f, 0.16f, 0.48f, 1.00f);
	Colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
	Colors[ImGuiCol_MenuBarBg]              = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
	Colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	Colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	Colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	Colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	Colors[ImGuiCol_CheckMark]              = ImVec4(0.45f, 0.26f, 0.98f, 1.00f);
	Colors[ImGuiCol_SliderGrab]             = ImVec4(0.41f, 0.00f, 1.00f, 0.40f);
	Colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.48f, 0.26f, 0.98f, 0.52f);
	Colors[ImGuiCol_Button]                 = ImVec4(0.20f, 0.20f, 0.20f, 0.40f);
	Colors[ImGuiCol_ButtonHovered]          = ImVec4(1.00f, 1.00f, 1.00f, 0.04f);
	Colors[ImGuiCol_ButtonActive]           = ImVec4(0.34f, 0.06f, 0.98f, 1.00f);
	Colors[ImGuiCol_Header]                 = ImVec4(1.00f, 1.00f, 1.00f, 0.04f);
	Colors[ImGuiCol_HeaderHovered]          = ImVec4(0.15f, 0.15f, 0.15f, 0.80f);
	Colors[ImGuiCol_HeaderActive]           = ImVec4(1.00f, 1.00f, 1.00f, 0.04f);
	Colors[ImGuiCol_Separator]              = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	Colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
	Colors[ImGuiCol_SeparatorActive]        = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
	Colors[ImGuiCol_ResizeGrip]             = ImVec4(1.00f, 1.00f, 1.00f, 0.04f);
	Colors[ImGuiCol_ResizeGripHovered]      = ImVec4(1.00f, 1.00f, 1.00f, 0.13f);
	Colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
	Colors[ImGuiCol_TabHovered]             = ImVec4(0.40f, 0.26f, 0.98f, 0.50f);
	Colors[ImGuiCol_Tab]                    = ImVec4(0.18f, 0.20f, 0.58f, 0.73f);
	Colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	Colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	Colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	Colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	Colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
	Colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
	Colors[ImGuiCol_TableBorderLight]       = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
	Colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	Colors[ImGuiCol_TableRowBgAlt]          = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
	Colors[ImGuiCol_TextSelectedBg]         = ImVec4(1.00f, 1.00f, 1.00f, 0.04f);
	Colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	Colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	Colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	Colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
}

