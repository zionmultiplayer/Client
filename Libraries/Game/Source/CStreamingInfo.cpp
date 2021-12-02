/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "CStreamingInfo.h"

PLUGIN_SOURCE_FILE

CStreamingInfo *&CStreamingInfo::ms_pArrayBase = *reinterpret_cast<CStreamingInfo **>(0x9654B4);

void CStreamingInfo::AddToList(CStreamingInfo *listStart) {
    plugin::CallMethodDynGlobal<CStreamingInfo *, CStreamingInfo *>(0x407480, this, listStart);
}

unsigned int CStreamingInfo::GetCdPosn() {
    return plugin::CallMethodAndReturnDynGlobal<unsigned int, CStreamingInfo *>(0x407570, this);
}

bool CStreamingInfo::GetCdPosnAndSize(unsigned int *CdPosn, unsigned int *CdSize) {
    return plugin::CallMethodAndReturnDynGlobal<bool, CStreamingInfo *, unsigned int *, unsigned int *>(0x4075A0, this, CdPosn, CdSize);
}

unsigned int CStreamingInfo::GetCdSize() {
    return plugin::CallMethodAndReturnDynGlobal<unsigned int, CStreamingInfo *>(0x407590, this);
}

CStreamingInfo *CStreamingInfo::GetNext() {
    return plugin::CallMethodAndReturnDynGlobal<CStreamingInfo *, CStreamingInfo *>(0x407520, this);
}

CStreamingInfo *CStreamingInfo::GetPrev() {
    return plugin::CallMethodAndReturnDynGlobal<CStreamingInfo *, CStreamingInfo *>(0x407540, this);
}

bool CStreamingInfo::InList() {
    return plugin::CallMethodAndReturnDynGlobal<bool, CStreamingInfo *>(0x407560, this);
}

void CStreamingInfo::Init() {
    plugin::CallMethodDynGlobal<CStreamingInfo *>(0x407460, this);
}

void CStreamingInfo::RemoveFromList() {
    plugin::CallMethodDynGlobal<CStreamingInfo *>(0x4074E0, this);
}

void CStreamingInfo::SetCdPosnAndSize(unsigned int CdPosn, unsigned int CdSize) {
    plugin::CallMethodDynGlobal<CStreamingInfo *, unsigned int, unsigned int>(0x4075E0, this, CdPosn, CdSize);
}
