#include "Zion/Gui.hh"
#include "Zion/SpawnScreen.hh"
#include "Zion/ChatWindow.hh"
#include "Zion/PlayerTag.hh"
#include "Zion/Dialog.hh"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"
#include "Game/CPad.h"
#include "Game/RenderWare.h"

void Zion::Gui::Init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplWin32_Init(GetForegroundWindow());
    ImGui_ImplDX9_Init(GetD3DDevice());
}

void Zion::Gui::Free()
{
    ImGui_ImplWin32_Shutdown();
    ImGui_ImplDX9_Shutdown();
    ImGui::DestroyContext();
}

void Zion::Gui::Render()
{
    ImGui_ImplWin32_NewFrame();
    ImGui_ImplDX9_NewFrame();
    ImGui::NewFrame();

    Zion::PlayerTag::Render();
    Zion::SpawnScreen::Render();
    Zion::Dialog::Render();
    Zion::ChatWindow::Render();

    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

void Zion::Gui::Process()
{
    ImGuiIO &io = ImGui::GetIO();

    unsigned char keyStates[256];
    GetKeyboardState(keyStates);

    for(int index = 0; index < 256; index++)
    {
        if(keyStates[index] & 0x80 && !io.KeysDown[index])
        {
            io.KeysDown[index] = true;

            char res[2] = {0};
            if(ToAscii(index, MapVirtualKey(index, 0), keyStates, (LPWORD)res, 0) == 1)
                io.AddInputCharactersUTF8(res);
        }
        else if (!(keyStates[index] & 0x80) && io.KeysDown[index])
            io.KeysDown[index] = false;
    }

    io.KeyCtrl = (GetKeyState(VK_CONTROL) & 0x8000);
    io.KeyShift = (GetKeyState(VK_SHIFT) & 0x8000);
    io.KeyAlt = (GetKeyState(VK_MENU) & 0x8000);
    io.KeySuper = false;

    io.MousePos = ImVec2(CPad::NewMouseControllerState.X, CPad::NewMouseControllerState.Y);
    io.MouseDown[0] = CPad::NewMouseControllerState.lmb;
    io.MouseDown[1] = CPad::NewMouseControllerState.mmb;
    io.MouseDown[2] = CPad::NewMouseControllerState.rmb;
}