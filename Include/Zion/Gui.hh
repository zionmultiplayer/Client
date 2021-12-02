#pragma once

namespace Zion
{
    class Gui
    {
        public:
            static void Init();
            static void Free();
            static void Render();
            static void Process();
    };
};