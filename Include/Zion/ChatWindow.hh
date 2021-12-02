#pragma once

namespace Zion
{
    class ChatWindow
    {
        public:
            static void Show(bool show);
            static void Open();
            static void Close();
            static void AddChat(const char *nickname, unsigned int nicknameColor, const char *text, unsigned int textColor);
            static void Process();
            static void Render();
    };
};