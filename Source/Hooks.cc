#include "Zion/Hooks.hh"
#include "Zion/Cursor.hh"
#include "Zion/SpawnScreen.hh"
#include "Zion/ChatWindow.hh"
#include "Zion/TextDraw.hh"
#include "Zion/Client.hh"
#include "Zion/Gui.hh"
#include "Zion/LocalPlayer.hh"
#include "Game/CFileMgr.h"
#include "Game/CTimer.h"
#include "Game/CPlayerPed.h"
#include "Game/CPool.h"
#include "Game/CLoadingScreen.h"
#include "Game/CTxdStore.h"
#include "SubHook/subhook.h"

class Hook
{
    public:
        static void Render2DStuffs();

        static subhook::Hook hkRender2DStuffs;

        class CGame
        {
            public:
                static void GameProcess();

                static subhook::Hook hkGameProcess;
        };

        class CPlayerPed : public ::CPlayerPed
        {
            public:
                CPad *GetPadFromPlayer();

                static subhook::Hook hkGetPadFromPlayer;
        };

        class CFileMgr {
            public:
                static FILESTREAM OpenFile(const char *path, const char *mode);

                static subhook::Hook hkOpenFile;
        };
};

subhook::Hook Hook::hkRender2DStuffs;
subhook::Hook Hook::CGame::hkGameProcess;
subhook::Hook Hook::CPlayerPed::hkGetPadFromPlayer;
subhook::Hook Hook::CFileMgr::hkOpenFile;

void Hook::Render2DStuffs()
{
    ((void (*)())hkRender2DStuffs.GetTrampoline())();

    Zion::TextDraw::Render_();
    Zion::Gui::Render();
    Zion::Cursor::Render();
}

void Hook::CGame::GameProcess()
{
    static int lastAttempt = 0;

    if(Zion::Client::state == Zion::Client::State::Connected)
    {
        Zion::SpawnScreen::Process();
        Zion::LocalPlayer::Process();
        Zion::ChatWindow::Process();
        Zion::TextDraw::Process_();
    }
    else if(Zion::Client::state == Zion::Client::State::Disconnected)
    {
        if(CTimer::m_snTimeInMilliseconds - lastAttempt >= 5000)
        {
            Zion::Client::Connect();
            lastAttempt = CTimer::m_snTimeInMilliseconds;
        }
    }

    Zion::Client::Process();
    Zion::Gui::Process();

    ((void (*)())hkGameProcess.GetTrampoline())();
}

CPad *Hook::CPlayerPed::GetPadFromPlayer()
{
    if(this->m_nPedType == PED_TYPE_PLAYER1)
        return CPad::GetPad(0);

    for(unsigned long index = 0; index < Zion::Client::players.GetLength(); index++)
    {
        Zion::RemotePlayer *remotePlayer = Zion::Client::players[index];

        if(remotePlayer != nullptr)
        {
            if(this == remotePlayer->ped)
                return remotePlayer->pad;
        }
    }

    return nullptr;
}

FILESTREAM Hook::CFileMgr::OpenFile(const char *path, const char *mode)
{
    if(strcmp(path, "DATA\\MAPS\\interior\\props.IDE ") == 0)
    {
        ::CFileMgr::SetDir("");
        path = "zion/data/maps/interior/props.ide";
    }
    else if(strcmp(path, "DATA\\MAPS\\LA\\LAn2.IDE ") == 0)
    {
        ::CFileMgr::SetDir("");
        path = "zion/data/maps/la/lan2.ide";
    }
    else if(strcmp(path, "DATA\\MAPS\\LA\\LAw2.IDE ") == 0)
    {
        ::CFileMgr::SetDir("");
        path = "zion/data/maps/la/law2.ide";
    }
    else if(strcmp(path, "DATA\\MAPS\\LA\\LAxref.IDE ") == 0)
    {
        ::CFileMgr::SetDir("");
        path = "zion/data/maps/la/laxref.ide";
    }
    else if(strcmp(path, "main.scm") == 0)
    {
        ::CFileMgr::SetDir("");
        path = "zion/data/script/main.scm";
    }
    else if(strcmp(path, "data\\script\\main.scm") == 0)
    {
        ::CFileMgr::SetDir("");
        path = "zion/data/script/main.scm";
    }
    else if(strcmp(path, "DATA\\AR_STATS.DAT") == 0)
    {
        ::CFileMgr::SetDir("");
        path = "zion/data/ar_stats.dat";
    }
    else if(strcmp(path, "DATA\\CARMODS.DAT") == 0)
    {
        ::CFileMgr::SetDir("");
        path = "zion/data/carmods.dat";
    }
    else if(strcmp(path, "DATA\\DEFAULT.DAT") == 0)
    {
        ::CFileMgr::SetDir("");
        path = "zion/data/default.dat";
    }
    else if(strcmp(path, "DATA\\DEFAULT.IDE ") == 0)
    {
        ::CFileMgr::SetDir("");
        path = "zion/data/default.ide";
    }
    else if(strcmp(path, "DATA\\GTA.DAT") == 0)
    {
        ::CFileMgr::SetDir("");
        path = "zion/data/gta.dat";
    }
    else if(strcmp(path, "HANDLING.CFG") == 0)
    {
        ::CFileMgr::SetDir("");
        path = "zion/data/handling.cfg";
    }
    else if(strcmp(path, "DATA\\melee.dat") == 0)
    {
        ::CFileMgr::SetDir("");
        path = "zion/data/melee.dat";
    }
    else if(strcmp(path, "DATA\\OBJECT.DAT") == 0)
    {
        ::CFileMgr::SetDir("");
        path = "zion/data/object.dat";
    }
    else if(strcmp(path, "DATA\\PED.DAT") == 0)
    {
        ::CFileMgr::SetDir("");
        path = "zion/data/ped.dat";
    }
    else if(strcmp(path, "DATA\\PEDS.IDE ") == 0)
    {
        ::CFileMgr::SetDir("");
        path = "zion/data/peds.ide";
    }
    else if(strcmp(path, "data\\shopping.dat") == 0)
    {
        ::CFileMgr::SetDir("");
        path = "zion/data/shopping.dat";
    }
    else if(strcmp(path, "data\\surface.dat") == 0)
    {
        ::CFileMgr::SetDir("");
        path = "zion/data/surface.dat";
    }
    else if(strcmp(path, "TIMECYC.DAT") == 0)
    {
        ::CFileMgr::SetDir("");
        path = "zion/data/timecyc.dat";
    }
    else if(strcmp(path, "DATA\\VEHICLES.IDE ") == 0)
    {
        ::CFileMgr::SetDir("");
        path = "zion/data/vehicles.ide";
    }
    else if(strcmp(path, "DATA\\WEAPON.DAT") == 0)
    {
        ::CFileMgr::SetDir("");
        path = "zion/data/weapon.dat";
    }
    else if(strcmp(path, "stream.ini") == 0)
    {
        ::CFileMgr::SetDir("");
        path = "zion/stream.ini";
    }

    return ((FILESTREAM (*)(const char *, const char *))hkOpenFile.GetTrampoline())(path, mode);
}

void Zion::Hooks::InstallBeforeGame()
{
    Hook::CFileMgr::hkOpenFile.Install((void *)0x538900, (void *)&Hook::CFileMgr::OpenFile);
}

void Zion::Hooks::Install()
{
    Hook::hkRender2DStuffs.Install((void *)0x53E230, (void *)Hook::Render2DStuffs);
    Hook::CGame::hkGameProcess.Install((void *)0x53BEE0, (void *)Hook::CGame::GameProcess);
    Hook::CPlayerPed::hkGetPadFromPlayer.Install((void *)0x609560, (void *)&Hook::CPlayerPed::GetPadFromPlayer);
}

void Zion::Hooks::Free()
{
    Hook::hkRender2DStuffs.Remove();
    Hook::CGame::hkGameProcess.Remove();
    Hook::CPlayerPed::hkGetPadFromPlayer.Remove();
    Hook::CFileMgr::hkOpenFile.Remove();
}