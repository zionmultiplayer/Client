#include "Zion/Cursor.hh"
#include "Game/RenderWare.h"
#include "Game/CTxdStore.h"
#include "Game/CSprite2d.h"
#include "SubHook/subhook.h"

static CSprite2d sprite;

class Hook
{
    public:
        static void _psMouseSetPos(RwV2d *position);

        static subhook::Hook hk_psMouseSetPos;
};

subhook::Hook Hook::hk_psMouseSetPos;

void Hook::_psMouseSetPos(RwV2d *position)
{
    if(Zion::Cursor::allowMovement == false)
        ((void (*)(RwV2d *))hk_psMouseSetPos.GetTrampoline())(position);
}

void Zion::Cursor::Init()
{
    Hook::hk_psMouseSetPos.Install((void *)0x7453F0, (void *)Hook::_psMouseSetPos);

    int txd = CTxdStore::AddTxdSlot("Zion_Mouse");
    if(CTxdStore::LoadTxd(txd, "models/fronten_pc.txd"))
    {
        CTxdStore::AddRef(txd);
        CTxdStore::PushCurrentTxd();
        CTxdStore::SetCurrentTxd(txd);
        sprite.SetTexture((char *)"mouse", (char *)"mousea");
        CTxdStore::PopCurrentTxd();
    }
}

void Zion::Cursor::Free()
{
    Hook::hk_psMouseSetPos.Remove();
}

void Zion::Cursor::SetCursorPosition(float x, float y)
{
    RwV2d position;
    position.x = x;
    position.y = y;
    ((void (*)(RwV2d *))0x7453F0)(&position);
}

void Zion::Cursor::Render()
{
    if(show == false || sprite.m_pTexture == nullptr)
        return;

    POINT position;
    GetCursorPos(&position);

    sprite.Draw(CRect(
        position.x, position.y, position.x + 18.0F, position.y + 18.0F), CRGBA(255, 255, 255, 255));
}

bool Zion::Cursor::show = false;
bool Zion::Cursor::allowMovement = false;