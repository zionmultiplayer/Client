#pragma once

namespace Zion
{
    class Hooks
    {
        public:
            static void InstallBeforeGame();
            static void Install();
            static void Free();
    };
};