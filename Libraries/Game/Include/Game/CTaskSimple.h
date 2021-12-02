/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Base.h"
#include "CTask.h"

class CTaskSimple : public CTask {
protected:
    CTaskSimple() : CTask() {}
public:
	virtual bool ProcessPed(class CPed *ped);//=0
	virtual bool SetPedPosition(class CPed *ped);
};

VALIDATE_SIZE(CTaskSimple, 8);