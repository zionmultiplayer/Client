#pragma once

namespace Zion
{
    class Cursor
    {
        public:
            static void Init();
            static void Free();
            static void SetCursorPosition(float x, float y);
            static void Render();

            static bool show;
            static bool allowMovement;
    };
};