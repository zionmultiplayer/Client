/*
    Plugin-SDK (Grand Theft Auto) SHARED header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#define VALIDATE_SIZE(struc, size) static_assert(sizeof(struc) == size, "Invalid structure size of " #struc)
#define VALIDATE_OFFSET(struc, member, offset) \
	static_assert(offsetof(struc, member) == offset, "The offset of " #member " in " #struc " is not " #offset "...")

VALIDATE_SIZE(bool, 1);
VALIDATE_SIZE(char, 1);
VALIDATE_SIZE(short, 2);
VALIDATE_SIZE(int, 4);
VALIDATE_SIZE(float, 4);
VALIDATE_SIZE(long long, 8);

// Basic types for structures describing
typedef unsigned char bool8;
typedef int bool32;
typedef long long int64;
typedef unsigned long long uint64;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

#if (defined(__GNUC__) || defined(__GNUG__) || defined(__clang__))
#define PLUGIN_SOURCE_FILE
#define PLUGIN_VARIABLE
#define _NOINLINE_
#elif (defined(_MSC_VER))
#define PLUGIN_SOURCE_FILE  __pragma(init_seg(lib))
#define PLUGIN_VARIABLE
#define _NOINLINE_ __declspec(noinline)
#else
#define PLUGIN_SOURCE_FILE
#define PLUGIN_VARIABLE
#define _NOINLINE_
#endif

#define PLUGIN_NO_DEFAULT_CONSTRUCTION(className) \
    className() = delete;\
    className(className const &) = delete;\
    className(className &&) = delete;\
    ~className() = delete;\
    className &operator=(className &&) = delete;

namespace plugin {
    template <unsigned int address, typename... Args>
    void Call(Args... args) {
        reinterpret_cast<void(__cdecl *)(Args...)>(address)(args...);
    }

    template <typename Ret, unsigned int address, typename... Args>
    Ret CallAndReturn(Args... args) {
        return reinterpret_cast<Ret(__cdecl *)(Args...)>(address)(args...);
    }

    template <unsigned int address, typename C, typename... Args>
    void CallMethod(C _this, Args... args) {
        reinterpret_cast<void(__thiscall *)(C, Args...)>(address)(_this, args...);
    }

    template <typename Ret, unsigned int address, typename C, typename... Args>
    Ret CallMethodAndReturn(C _this, Args... args) {
        return reinterpret_cast<Ret(__thiscall *)(C, Args...)>(address)(_this, args...);
    }

    template <unsigned int tableIndex, typename C, typename... Args>
    void CallVirtualMethod(C _this, Args... args) {
        reinterpret_cast<void(__thiscall *)(C, Args...)>((*reinterpret_cast<void ***>(_this))[tableIndex])(_this, args...);
    }

    template <typename Ret, unsigned int tableIndex, typename C, typename... Args>
    Ret CallVirtualMethodAndReturn(C _this, Args... args) {
        return reinterpret_cast<Ret(__thiscall *)(C, Args...)>((*reinterpret_cast<void ***>(_this))[tableIndex])(_this, args...);
    }

    template <typename... Args>
    void CallDynGlobal(unsigned int address, Args... args) {
        reinterpret_cast<void(__cdecl *)(Args...)>(address)(args...);
    }

    template <typename Ret, typename... Args>
    Ret CallAndReturnDynGlobal(unsigned int address, Args... args) {
        return reinterpret_cast<Ret(__cdecl *)(Args...)>(address)(args...);
    }

    template <typename C, typename... Args>
    void CallMethodDynGlobal(unsigned int address, C _this, Args... args) {
        reinterpret_cast<void(__thiscall *)(C, Args...)>(address)(_this, args...);
    }

    template <typename Ret, typename C, typename... Args>
    Ret CallMethodAndReturnDynGlobal(unsigned int address, C _this, Args... args) {
        return reinterpret_cast<Ret(__thiscall *)(C, Args...)>(address)(_this, args...);
    }

    // Gets the virtual method table from the object @self
    inline void** GetVMT(const void* self) {
        return *(void***)(self);
    }

    // Gets the virtual method from @self in the table index @index 
    inline void* GetVMT(const void* self, unsigned long index) {
        return GetVMT(self)[index];
    }
};