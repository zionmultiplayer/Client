#pragma once

namespace Zion
{
    class Log
    {
        public:
            static void Open(const char *filename);
            static void Close();
            static void Write(const char *format, ...);
    };
};