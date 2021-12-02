#include "Zion/Util.hh"
#include "Game/CTimer.h"
#include <windows.h>

float Zion::Util::DegressToRadians(float degress)
{
    return degress * 0.01745F;
}

bool Zion::Util::IsKeyPressed(int keyCode)
{
    static int lkp = 0;

    if(GetKeyState(keyCode) & 0x8000 && CTimer::m_snTimeInMilliseconds - lkp >= 500)
    {
        lkp = CTimer::m_snTimeInMilliseconds;
        return true;
    }

    return false;
}