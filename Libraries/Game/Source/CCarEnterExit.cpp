/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "CCarEnterExit.h"

PLUGIN_SOURCE_FILE

float const &CCarEnterExit::ms_fMaxSpeed_CanDragPedOut = *reinterpret_cast<float const *>(0x86F104);
float const &CCarEnterExit::ms_fMaxSpeed_PlayerCanDragPedOut = *reinterpret_cast<float const *>(0x86F108);
bool &CCarEnterExit::ms_bPedOffsetsCalculated = *reinterpret_cast<bool *>(0xC18C20);
CVector &CCarEnterExit::ms_vecPedGetUpAnimOffset = *reinterpret_cast<CVector *>(0xC18C3C);
CVector &CCarEnterExit::ms_vecPedQuickDraggedOutCarAnimOffset = *reinterpret_cast<CVector *>(0xC18C48);
CVector &CCarEnterExit::ms_vecPedBedLAnimOffset = *reinterpret_cast<CVector *>(0xC18C54);
CVector &CCarEnterExit::ms_vecPedBedRAnimOffset = *reinterpret_cast<CVector *>(0xC18C60);
CVector &CCarEnterExit::ms_vecPedDeskAnimOffset = *reinterpret_cast<CVector *>(0xC18C6C);
CVector &CCarEnterExit::ms_vecPedChairAnimOffset = *reinterpret_cast<CVector *>(0xC18C78);

void CCarEnterExit::AddInCarAnim(CVehicle const *vehicle, CPed *ped, bool bAsDriver) {
    plugin::CallDynGlobal<CVehicle const *, CPed *, bool>(0x64F720, vehicle, ped, bAsDriver);
}

bool CCarEnterExit::CarHasDoorToClose(CVehicle const *vehicle, int doorId) {
    return plugin::CallAndReturnDynGlobal<bool, CVehicle const *, int>(0x64EE10, vehicle, doorId);
}

bool CCarEnterExit::CarHasDoorToOpen(CVehicle const *vehicle, int doorID) {
    return plugin::CallAndReturnDynGlobal<bool, CVehicle const *, int>(0x64EDD0, vehicle, doorID);
}

bool CCarEnterExit::CarHasOpenableDoor(CVehicle const *vehicle, int DoorID_UnusedArg, CPed const *ped) {
    return plugin::CallAndReturnDynGlobal<bool, CVehicle const *, int, CPed const *>(0x64EE50, vehicle, DoorID_UnusedArg, ped);
}

bool CCarEnterExit::CarHasPartiallyOpenDoor(CVehicle const *vehicle, int doorID) {
    return plugin::CallAndReturnDynGlobal<bool, CVehicle const *, int>(0x64EE70, vehicle, doorID);
}

int CCarEnterExit::ComputeDoorFlag(CVehicle const *vehicle, int doorId, bool bCheckVehicleType) {
    return plugin::CallAndReturnDynGlobal<int, CVehicle const *, int, bool>(0x64E550, vehicle, doorId, bCheckVehicleType);
}

int CCarEnterExit::ComputeOppositeDoorFlag(CVehicle const *vehicle, int doorId, bool bCheckVehicleType) {
    return plugin::CallAndReturnDynGlobal<int, CVehicle const *, int, bool>(0x64E610, vehicle, doorId, bCheckVehicleType);
}

signed int CCarEnterExit::ComputePassengerIndexFromCarDoor(CVehicle const *vehicle, int doorID) {
    return plugin::CallAndReturnDynGlobal<signed int, CVehicle const *, int>(0x64F1E0, vehicle, doorID);
}

int CCarEnterExit::ComputeSlowJackedPed(CVehicle const *vehicle, int doorID) {
    return plugin::CallAndReturnDynGlobal<int, CVehicle const *, int>(0x64F070, vehicle, doorID);
}

signed int CCarEnterExit::ComputeTargetDoorToEnterAsPassenger(CVehicle const *pVehicle, int nPassengerNum) {
    return plugin::CallAndReturnDynGlobal<signed int, CVehicle const *, int>(0x64F190, pVehicle, nPassengerNum);
}

int CCarEnterExit::ComputeTargetDoorToExit(CVehicle const *pVehicle, CPed const *pPed) {
    return plugin::CallAndReturnDynGlobal<int, CVehicle const *, CPed const *>(0x64F110, pVehicle, pPed);
}

bool CCarEnterExit::GetNearestCarDoor(CPed const *pPed, CVehicle const *pVehicle, CVector *outPos, int doorID) {
    return plugin::CallAndReturnDynGlobal<bool, CPed const *, CVehicle const *, CVector *, int>(0x6528F0, pPed, pVehicle, outPos, doorID);
}

bool CCarEnterExit::GetNearestCarPassengerDoor(CPed const *ped, CVehicle const *vehicle, CVector *outVec, int *doorId, bool flag1, bool flag2, bool flag3) {
    return plugin::CallAndReturnDynGlobal<bool, CPed const *, CVehicle const *, CVector *, int *, bool, bool, bool>(0x650BB0, ped, vehicle, outVec, doorId, flag1, flag2, flag3);
}

CVector *CCarEnterExit::GetPositionToOpenCarDoor(CVector *out, CVehicle const *vehicle, int doorId) {
    return plugin::CallAndReturnDynGlobal<CVector *, CVector *, CVehicle const *, int>(0x64E740, out, vehicle, doorId);
}

bool CCarEnterExit::IsCarDoorInUse(CVehicle const *vehicle, int door1Id, int door2Id) {
    return plugin::CallAndReturnDynGlobal<bool, CVehicle const *, int, int>(0x64EC90, vehicle, door1Id, door2Id);
}

bool CCarEnterExit::IsCarDoorReady(CVehicle const *vehicle, int doorID) {
    return plugin::CallAndReturnDynGlobal<bool, CVehicle const *, int>(0x64ED90, vehicle, doorID);
}

bool CCarEnterExit::IsCarQuickJackPossible(CVehicle const *vehicle, int doorID, CPed const *ped) {
    return plugin::CallAndReturnDynGlobal<bool, CVehicle const *, int, CPed const *>(0x64EF00, vehicle, doorID, ped);
}

bool CCarEnterExit::IsCarSlowJackRequired(CVehicle const *vehicle, int doorID) {
    return plugin::CallAndReturnDynGlobal<bool, CVehicle const *, int>(0x64EF70, vehicle, doorID);
}

bool CCarEnterExit::IsClearToDriveAway(CVehicle const *outVehicle) {
    return plugin::CallAndReturnDynGlobal<bool, CVehicle const *>(0x6509B0, outVehicle);
}

bool CCarEnterExit::IsPathToDoorBlockedByVehicleCollisionModel(CPed const *ped, CVehicle *vehicle, CVector const *pos) {
    return plugin::CallAndReturnDynGlobal<bool, CPed const *, CVehicle *, CVector const *>(0x651210, ped, vehicle, pos);
}

bool CCarEnterExit::IsPedHealthy(CPed *vehicle) {
    return plugin::CallAndReturnDynGlobal<bool, CPed *>(0x64EEE0, vehicle);
}

bool CCarEnterExit::IsPlayerToQuitCarEnter(CPed const *ped, CVehicle const *vehicle, int StartTime, CTask *task) {
    return plugin::CallAndReturnDynGlobal<bool, CPed const *, CVehicle const *, int, CTask *>(0x64F240, ped, vehicle, StartTime, task);
}

bool CCarEnterExit::IsRoomForPedToLeaveCar(CVehicle const *veh, int doorID, CVector *pos) {
    return plugin::CallAndReturnDynGlobal<bool, CVehicle const *, int, CVector *>(0x6504C0, veh, doorID, pos);
}

bool CCarEnterExit::IsVehicleHealthy(CVehicle const *vehicle) {
    return plugin::CallAndReturnDynGlobal<bool, CVehicle const *>(0x64EEC0, vehicle);
}

bool CCarEnterExit::IsVehicleStealable(CVehicle const *vehicle, CPed const *ped) {
    return plugin::CallAndReturnDynGlobal<bool, CVehicle const *, CPed const *>(0x6510D0, vehicle, ped);
}

void CCarEnterExit::MakeUndraggedDriverPedLeaveCar(CVehicle const *vehicle, CPed const *ped) {
    plugin::CallDynGlobal<CVehicle const *, CPed const *>(0x64F600, vehicle, ped);
}

void CCarEnterExit::MakeUndraggedPassengerPedsLeaveCar(CVehicle const *targetVehicle, CPed const *draggedPed, CPed const *ped) {
    plugin::CallDynGlobal<CVehicle const *, CPed const *, CPed const *>(0x64F540, targetVehicle, draggedPed, ped);
}

void CCarEnterExit::QuitEnteringCar(CPed *ped, CVehicle *vehicle, int doorID, bool bCarWasBeingJacked) {
    plugin::CallDynGlobal<CPed *, CVehicle *, int, bool>(0x650130, ped, vehicle, doorID, bCarWasBeingJacked);
}

void CCarEnterExit::RemoveCarSitAnim(CPed const *ped) {
    plugin::CallDynGlobal<CPed const *>(0x64F680, ped);
}

void CCarEnterExit::RemoveGetInAnims(CPed const *ped) {
    plugin::CallDynGlobal<CPed const *>(0x64F6E0, ped);
}

void CCarEnterExit::SetAnimOffsetForEnterOrExitVehicle() {
    plugin::CallDynGlobal(0x64F860);
}

void CCarEnterExit::SetPedInCarDirect(CPed *ped, CVehicle *vehicle, int seatNumber, bool bAsDriver) {
    plugin::CallDynGlobal<CPed *, CVehicle *, int, bool>(0x650280, ped, vehicle, seatNumber, bAsDriver);
}
