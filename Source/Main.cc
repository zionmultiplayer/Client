#include "Zion/Main.hh"
#include "Zion/Client.hh"
#include "Zion/Cursor.hh"
#include "Zion/Hooks.hh"
#include "Zion/Gui.hh"
#include "Zion/Log.hh"
#include "Zion/Patches.hh"
#include <pthread.h>
#include <windows.h>
#include <imagehlp.h>

CPlayerPed *Zion::Main::player = nullptr;
CPad *Zion::Main::pad = nullptr;

static unsigned int &systemState = *(unsigned int *)0xC8D4C0;
static bool &gameStarted = *(bool *)0xBA6831;
static bool &menuVisible = *(bool *)0xBA67A4;
static bool &isAtMenu = *(bool *)0xBA677B;

static void PreInit()
{
    Zion::Log::Open("zion/log.txt");
    Zion::Patches::InstallBeforeGame();
    Zion::Hooks::InstallBeforeGame();
}

static void Init() 
{
    Zion::Client::nickname = "localhost";
    Zion::Client::hostname = "localhost";
    Zion::Client::port = 7777;

    Zion::Patches::Install();
    Zion::Hooks::Install();
    Zion::Cursor::Init();
    Zion::Gui::Init();
}

static void Free()
{
    Zion::Client::Disconnect();
    Zion::Hooks::Free();
    Zion::Gui::Free();
    Zion::Cursor::Free();
    Zion::Log::Close();

    Zion::Client::nickname = nullptr;
    Zion::Client::hostname = nullptr;
    Zion::Client::port = 0;
    Zion::Main::player = nullptr;
    Zion::Main::pad = nullptr;
}

static void StartGame()
{
    systemState = 8;
    gameStarted = true;
    menuVisible = false;
    isAtMenu = false;
}

LONG WINAPI ExceptionHandler(EXCEPTION_POINTERS* exceptionPointers)
{
    Zion::Log::Write("[ERROR] unhandled exception 0x%X at 0x%X\n",
        exceptionPointers->ExceptionRecord->ExceptionCode,
        exceptionPointers->ExceptionRecord->ExceptionAddress);

    Free();
    return EXCEPTION_EXECUTE_FAULT;
}

static void *Launch(void *)
{
    while(true)
    {
        if(systemState == 7)
        {
            Init();
            StartGame();
            break;
        }
    }

    return nullptr;
}

BOOL WINAPI DllMain(HINSTANCE hinstance, DWORD reason, LPVOID reserved)
{
    if(reason == DLL_PROCESS_ATTACH)
    {
        SetUnhandledExceptionFilter(ExceptionHandler);
        PreInit();

        pthread_t thread;
        pthread_create(&thread, nullptr, Launch, nullptr);
    }
    else if(reason == DLL_PROCESS_DETACH)
        Free();

    return TRUE;
}