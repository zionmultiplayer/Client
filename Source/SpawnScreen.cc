#include "Zion/SpawnScreen.hh"
#include "Zion/LocalPlayer.hh"
#include "Zion/Cursor.hh"
#include "Zion/Client.hh"
#include "Zion/Main.hh"
#include "ImGui/imgui.h"

#define pad Zion::Main::pad

void Zion::SpawnScreen::Process()
{
    if(show)
    {
        pad->DisablePlayerControls = true;
        Cursor::show = true;
        Cursor::allowMovement = true;
    }
}

void Zion::SpawnScreen::Render()
{
    if(show == false)
        return;

    ImGui::Begin("SpawnScreen", nullptr, 
        ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | 
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings);

    if (ImGui::Button("<<", ImVec2(100, 30)))
        LocalPlayer::PreviousClass();
    
    ImGui::SameLine(0, 10);

    if (ImGui::Button("Spawn", ImVec2(100, 30)))
    {
        show = false;
        pad->DisablePlayerControls = false;
        Cursor::show = false;
        Cursor::allowMovement = false;
        Client::RequestSpawn();
    }

    ImGui::SameLine(0, 10);

    if (ImGui::Button(">>", ImVec2(100, 30)))
        LocalPlayer::NextClass();

    ImGui::SetWindowSize(ImVec2(-1, -1));
    ImVec2 size = ImGui::GetWindowSize();
    ImGuiIO &io = ImGui::GetIO();
    ImGui::SetWindowPos(
        ImVec2(((io.DisplaySize.x - size.x) / 2), ((io.DisplaySize.y * 0.95) - size.y)));
    
    ImGui::End();
}

bool Zion::SpawnScreen::show = false;