#pragma once

namespace Zion
{
    class Dialog
    {
        public:
            static void Open();
            static void Close();
            static void Render();
            static void Process();

            static unsigned short id;
            static unsigned char style;
            static char title[256];
            static char button1[256];
            static char button2[256];
            static char info[512];
    };
};