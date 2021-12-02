#include "Zion/ChatWindow.hh"
#include "Zion/Client.hh"
#include "Zion/Cursor.hh"
#include "Zion/List.hh"
#include "Zion/Main.hh"
#include "Zion/Util.hh"
#include "Game/CPad.h"
#include "Game/RenderWare.h"
#include "ImGui/imgui.h"

#define pad Zion::Main::pad

static bool show = true;
static bool open = false;

struct Chat
{
    char *nickname;
    unsigned int nicknameColor;
    char *text;
    unsigned int textColor;
};

static Zion::List<Chat> chats;
static char text[512] = {0};

void Zion::ChatWindow::Render()
{
    if(show == false)
        return;

    ImGui::Begin("ChatWindow", nullptr, 
        ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | 
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBackground);

    ImGui::BeginChild(1, ImVec2(RsGlobal.maximumWidth - 10.0F, RsGlobal.maximumHeight / 4), false,
        ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | 
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBackground);

    for(unsigned long index = 0; index < chats.GetLength(); index++)
    {
        Chat chat = chats[index];
        
        if(chat.nickname == nullptr)
            ImGui::TextColored(ImColor(chat.textColor), chat.text);
        else
        {
            ImGui::TextColored(ImColor(chat.nicknameColor), chat.nickname);
            ImGui::SameLine();
            ImGui::TextColored(ImColor(chat.textColor), chat.text);
        }
    }

    ImGui::EndChild();

    if(open)
    {
        ImGui::SetNextItemWidth(-1.0F);
        ImGui::InputText("", text, 512);
    }

    ImGui::SetWindowSize(ImVec2(RsGlobal.maximumWidth - 10.0F, -1));
    ImGui::SetWindowPos(ImVec2(10.0F, 10.0F));
    
    ImGui::End();
}

void Zion::ChatWindow::Show(bool show)
{
    ::show = show;   
}

void Zion::ChatWindow::Open()
{
    open = true;
    text[0] = 0;
}

void Zion::ChatWindow::Close()
{
    open = false;
    pad->DisablePlayerControls = false;
    Cursor::show = false;
    Cursor::allowMovement = false;
}

void Zion::ChatWindow::AddChat(const char *nickname, unsigned int nicknameColor, const char *text, unsigned int textColor)
{
    Chat chat;
    chat.nickname = strdup(nickname);
    chat.nicknameColor = nicknameColor;
    chat.text = strdup(text);
    chat.textColor = textColor;
    chats.Push(chat);
}

void Zion::ChatWindow::Process()
{
    if(open)
    {
        pad->DisablePlayerControls = true;
        Cursor::show = true;
        Cursor::allowMovement = true;

        if(Util::IsKeyPressed(VK_ESCAPE))
            Close();
        else if(Util::IsKeyPressed(VK_RETURN))
        {
            if(text[0] == '/')
                Client::SendCommand(text);
            else
                Client::SendMessage(text);

            Close();
        }
    }
    else if(Util::IsKeyPressed('T'))
        Open();
}