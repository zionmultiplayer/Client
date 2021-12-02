/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Base.h"
#include "CMatrix.h"

class CPlaceable;

class CMatrixLink : public CMatrix {
    PLUGIN_NO_DEFAULT_CONSTRUCTION(CMatrixLink)

public:
    CPlaceable *m_pOwner;
    CMatrixLink *m_pPrev;
    CMatrixLink *m_pNext;
};

VALIDATE_SIZE(CMatrixLink, 0x54);