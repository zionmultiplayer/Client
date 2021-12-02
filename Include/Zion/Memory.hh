#pragma once
#include <windows.h>

namespace Zion
{
    class Memory
    {
        public:
            template<typename T>
            static inline void Write(unsigned int address, T value)
            {
                DWORD oldProtect;
                VirtualProtect((void *)address, sizeof(T), PAGE_EXECUTE_READWRITE, &oldProtect);

                *(T *)address = value;

                DWORD tmp;
                VirtualProtect((void *)address, sizeof(T), oldProtect, &tmp);
            }

            template<typename T>
            static inline T Read(unsigned int address)
            {
                DWORD oldProtect;
                VirtualProtect((void *)address, sizeof(T), PAGE_EXECUTE_READWRITE, &oldProtect);

                T value = *(T *)address;

                DWORD tmp;
                VirtualProtect((void *)address, sizeof(T), oldProtect, &tmp);

                return value;
            }

            static inline void Copy(unsigned int address, void *data, unsigned long size)
            {
                DWORD oldProtect;
                VirtualProtect((void *)address, size, PAGE_EXECUTE_READWRITE, &oldProtect);

                memcpy((void *)address, data, size);

                DWORD tmp;
                VirtualProtect((void *)address, size, oldProtect, &tmp);
            }

            static inline void Set(unsigned int address, int value, unsigned long size)
            {
                DWORD oldProtect;
                VirtualProtect((void *)address, size, PAGE_EXECUTE_READWRITE, &oldProtect);

                memset((void *)address, value, size);

                DWORD tmp;
                VirtualProtect((void *)address, size, oldProtect, &tmp);
            }
    };
};