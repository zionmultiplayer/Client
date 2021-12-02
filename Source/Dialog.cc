#include "Zion/Dialog.hh"
#include "Zion/Gui.hh"
#include "Zion/Cursor.hh"
#include "Zion/Main.hh"
#include "Zion/Client.hh"
#include "ImGui/imgui.h"
#include "Game/CPad.h"
#include <string>

#define player Zion::Main::player
#define pad Zion::Main::pad

#define DIALOG_STYLE_MSGBOX             0
#define DIALOG_STYLE_INPUT              1
#define DIALOG_STYLE_LIST               2
#define DIALOG_STYLE_PASSWORD           3
#define DIALOG_STYLE_TABLIST            4
#define DIALOG_STYLE_TABLIST_HEADERS    5

unsigned short Zion::Dialog::id = 0;
unsigned char Zion::Dialog::style = 0;
char Zion::Dialog::title[256] = {0};
char Zion::Dialog::button1[256] = {0};
char Zion::Dialog::button2[256] = {0};
char Zion::Dialog::info[512] = {0};

static bool open = false;
static char buffer[512] = {0};

void Zion::Dialog::Open()
{
    open = true;
    buffer[0] = 0;
}

void Zion::Dialog::Close()
{
    open = false;
    pad->DisablePlayerControls = false;
    Cursor::show = false;
    Cursor::allowMovement = false;
}

void Zion::Dialog::Render()
{
    if(open == false)
        return;
    
    ImGui::Begin(title, nullptr,
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoSavedSettings);

    switch(style)
    {
        case DIALOG_STYLE_MSGBOX:
            ImGui::Text(info);
            break;

        case DIALOG_STYLE_INPUT:
            ImGui::Text(info);
            ImGui::SetNextItemWidth(-1);
            ImGui::InputText("", buffer, 512);
            break;

        case DIALOG_STYLE_PASSWORD:
            ImGui::Text(info);
            ImGui::SetNextItemWidth(-1);
            ImGui::InputText("", buffer, 512, ImGuiInputTextFlags_Password);
            break;
    }

    if(button1[0] != 0)
    {
        if(ImGui::Button(button1, ImVec2(100, 30)))
        {
            Client::SendDialogResponse(id, 1, -1, buffer);
            Close();
        }
    }

    if(button2[0] != 0)
    {
        ImGui::SameLine(0, 10);

        if(ImGui::Button(button2, ImVec2(100, 30)))
        {
            Client::SendDialogResponse(id, 0, -1, buffer);
            Close();
        }
    }

    ImGui::SetWindowSize(ImVec2(-1, -1));
    ImVec2 size = ImGui::GetWindowSize();
    ImGuiIO &io = ImGui::GetIO();
    ImGui::SetWindowPos(
        ImVec2(((io.DisplaySize.x - size.x) / 2), ((io.DisplaySize.y - size.y) / 2)));

    ImGui::End();
}

void Zion::Dialog::Process()
{
    if(open)
    {
        pad->DisablePlayerControls = true;
        Cursor::show = true;
        Cursor::allowMovement = true;
    }
}