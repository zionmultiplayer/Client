/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#include "CCamera.h"

PLUGIN_SOURCE_FILE

float &CCamera::m_f3rdPersonCHairMultY = *reinterpret_cast<float *>(0xB6EC10);
float &CCamera::m_f3rdPersonCHairMultX = *reinterpret_cast<float *>(0xB6EC14);
float &CCamera::m_fMouseAccelVertical = *reinterpret_cast<float *>(0xB6EC18);
float &CCamera::m_fMouseAccelHorzntl = *reinterpret_cast<float *>(0xB6EC1C);
bool &CCamera::m_bUseMouse3rdPerson = *reinterpret_cast<bool *>(0xB6EC2E);
CCamera &TheCamera = *reinterpret_cast<CCamera *>(0xB6F028);

void CCamera::AddShakeSimple(float duration, int type, float intensity) {
    plugin::CallMethodDynGlobal<CCamera *, float, int, float>(0x50D240, this, duration, type, intensity);
}

void CCamera::AllowShootingWith2PlayersInCar(bool bAllowShootingWith2PlayersInCar) {
    plugin::CallMethodDynGlobal<CCamera *, bool>(0x50C280, this, bAllowShootingWith2PlayersInCar);
}

void CCamera::ApplyVehicleCameraTweaks(CVehicle *vehicle) {
    plugin::CallMethodDynGlobal<CCamera *, CVehicle *>(0x50A480, this, vehicle);
}

void CCamera::AvoidTheGeometry(CVector const *arg2, CVector const *arg3, CVector *arg4, float FOV) {
    plugin::CallMethodDynGlobal<CCamera *, CVector const *, CVector const *, CVector *, float>(0x514030, this, arg2, arg3, arg4, FOV);
}

void CCamera::CalculateDerivedValues(bool bForMirror, bool bOriented) {
    plugin::CallMethodDynGlobal<CCamera *, bool, bool>(0x5150E0, this, bForMirror, bOriented);
}

void CCamera::CalculateFrustumPlanes(bool bForMirror) {
    plugin::CallMethodDynGlobal<CCamera *, bool>(0x514D60, this, bForMirror);
}

float CCamera::CalculateGroundHeight(unsigned int type) {
    return plugin::CallMethodAndReturnDynGlobal<float, CCamera *, unsigned int>(0x514B80, this, type);
}

void CCamera::CalculateMirroredMatrix(CVector posn, float MirrorV, CMatrix *CamMat, CMatrix *MirrorMat) {
    plugin::CallMethodDynGlobal<CCamera *, CVector, float, CMatrix *, CMatrix *>(0x50B380, this, posn, MirrorV, CamMat, MirrorMat);
}

void CCamera::CamControl() {
    plugin::CallMethodDynGlobal<CCamera *>(0x527FA0, this);
}

void CCamera::CamShake(float arg2, float x, float y, float z) {
    plugin::CallMethodDynGlobal<CCamera *, float, float, float, float>(0x50A9F0, this, arg2, x, y, z);
}

char CCamera::CameraColDetAndReact(CVector *source, CVector *target) {
    return plugin::CallMethodAndReturnDynGlobal<char, CCamera *, CVector *, CVector *>(0x520190, this, source, target);
}

void CCamera::CameraGenericModeSpecialCases(CPed *targetPed) {
    plugin::CallMethodDynGlobal<CCamera *, CPed *>(0x50CD30, this, targetPed);
}

void CCamera::CameraPedAimModeSpecialCases(CPed *targPed) {
    plugin::CallMethodDynGlobal<CCamera *, CPed *>(0x50CDA0, this, targPed);
}

void CCamera::CameraPedModeSpecialCases() {
    plugin::CallMethodDynGlobal<CCamera *>(0x50CD80, this);
}

void CCamera::CameraVehicleModeSpecialCases(CVehicle *targVehicle) {
    plugin::CallMethodDynGlobal<CCamera *, CVehicle *>(0x50CDE0, this, targVehicle);
}

void CCamera::ClearPlayerWeaponMode() {
    plugin::CallMethodDynGlobal<CCamera *>(0x50AB10, this);
}

bool CCamera::ConeCastCollisionResolve(CVector *source, CVector *center, CVector *pVecOut, float radius, float arg5, float *pFloatOut) {
    return plugin::CallMethodAndReturnDynGlobal<bool, CCamera *, CVector *, CVector *, CVector *, float, float, float *>(0x51A5D0, this, source, center, pVecOut, radius, arg5, pFloatOut);
}

bool CCamera::ConsiderPedAsDucking(CPed *ped) {
    return plugin::CallMethodAndReturnDynGlobal<bool, CCamera *, CPed *>(0x50CEB0, this, ped);
}

void CCamera::CopyCameraMatrixToRWCam(bool bUpdateMatrix) {
    plugin::CallMethodDynGlobal<CCamera *, bool>(0x50AFA0, this, bUpdateMatrix);
}

void CCamera::DealWithMirrorBeforeConstructRenderList(bool bActiveMirror, CVector MirrorNormal, float MirrorV, CMatrix *matMirror) {
    plugin::CallMethodDynGlobal<CCamera *, bool, CVector, float, CMatrix *>(0x50B510, this, bActiveMirror, MirrorNormal, MirrorV, matMirror);
}

void CCamera::DeleteCutSceneCamDataMemory() {
    plugin::CallMethodDynGlobal<CCamera *>(0x5B24A0, this);
}

void CCamera::DrawBordersForWideScreen() {
    plugin::CallMethodDynGlobal<CCamera *>(0x514860, this);
}

void CCamera::Enable1rstPersonCamCntrlsScript() {
    plugin::CallMethodDynGlobal<CCamera *>(0x50AC00, this);
}

void CCamera::Enable1rstPersonWeaponsCamera() {
    plugin::CallMethodDynGlobal<CCamera *>(0x50AC10, this);
}

void CCamera::Fade(float fadeDuration, short FadeInOutFlag) {
    plugin::CallMethodDynGlobal<CCamera *, float, short>(0x50AC20, this, fadeDuration, FadeInOutFlag);
}

void CCamera::Find3rdPersonCamTargetVector(float range, CVector source, CVector *pCamera, CVector *pPoint) {
    plugin::CallMethodDynGlobal<CCamera *, float, CVector, CVector *, CVector *>(0x514970, this, range, source, pCamera, pPoint);
}

float CCamera::Find3rdPersonQuickAimPitch() {
    return plugin::CallMethodAndReturnDynGlobal<float, CCamera *>(0x50AD40, this);
}

float CCamera::FindCamFOV() {
    return plugin::CallMethodAndReturnDynGlobal<float, CCamera *>(0x50AD20, this);
}

void CCamera::FinishCutscene() {
    plugin::CallMethodDynGlobal<CCamera *>(0x514950, this);
}

void CCamera::GetArrPosForVehicleType(int type, int *arrPos) {
    plugin::CallMethodDynGlobal<CCamera *, int, int *>(0x50AF00, this, type, arrPos);
}

unsigned int CCamera::GetCutSceneFinishTime() {
    return plugin::CallMethodAndReturnDynGlobal<unsigned int, CCamera *>(0x50AD90, this);
}

bool CCamera::GetFading() {
    return plugin::CallMethodAndReturnDynGlobal<bool, CCamera *>(0x50ADE0, this);
}

int CCamera::GetFadingDirection() {
    return plugin::CallMethodAndReturnDynGlobal<int, CCamera *>(0x50ADF0, this);
}

CVector *CCamera::GetGameCamPosition() {
    return plugin::CallMethodAndReturnDynGlobal<CVector *, CCamera *>(0x50AE50, this);
}

signed int CCamera::GetLookDirection() {
    return plugin::CallMethodAndReturnDynGlobal<signed int, CCamera *>(0x50AE90, this);
}

bool CCamera::GetLookingForwardFirstPerson() {
    return plugin::CallMethodAndReturnDynGlobal<bool, CCamera *>(0x50AED0, this);
}

bool CCamera::GetLookingLRBFirstPerson() {
    return plugin::CallMethodAndReturnDynGlobal<bool, CCamera *>(0x50AE60, this);
}

float CCamera::GetPositionAlongSpline() {
    return plugin::CallMethodAndReturnDynGlobal<float, CCamera *>(0x50AF80, this);
}

float CCamera::GetRoughDistanceToGround() {
    return plugin::CallMethodAndReturnDynGlobal<float, CCamera *>(0x516B00, this);
}

signed int CCamera::GetScreenFadeStatus() {
    return plugin::CallMethodAndReturnDynGlobal<signed int, CCamera *>(0x50AE20, this);
}

void CCamera::GetScreenRect(CRect *pRect) {
    plugin::CallMethodDynGlobal<CCamera *, CRect *>(0x50AB50, this, pRect);
}

bool CCamera::Get_Just_Switched_Status() {
    return plugin::CallMethodAndReturnDynGlobal<bool, CCamera *>(0x50AE10, this);
}

void CCamera::HandleCameraMotionForDucking(CPed *ped, CVector *source, CVector *targPosn, bool arg5) {
    plugin::CallMethodDynGlobal<CCamera *, CPed *, CVector *, CVector *, bool>(0x50CFA0, this, ped, source, targPosn, arg5);
}

void CCamera::HandleCameraMotionForDuckingDuringAim(CPed *ped, CVector *source, CVector *targPosn, bool arg5) {
    plugin::CallMethodDynGlobal<CCamera *, CPed *, CVector *, CVector *, bool>(0x50D090, this, ped, source, targPosn, arg5);
}

void CCamera::ImproveNearClip(CVehicle *pVehicle, CPed *pPed, CVector *source, CVector *targPosn) {
    plugin::CallMethodDynGlobal<CCamera *, CVehicle *, CPed *, CVector *, CVector *>(0x516B20, this, pVehicle, pPed, source, targPosn);
}

void CCamera::Init() {
    plugin::CallMethodDynGlobal<CCamera *>(0x5BC520, this);
}

void CCamera::InitCameraVehicleTweaks() {
    plugin::CallMethodDynGlobal<CCamera *>(0x50A3B0, this);
}

int CCamera::InitialiseScriptableComponents() {
    return plugin::CallMethodAndReturnDynGlobal<int, CCamera *>(0x50D2D0, this);
}

bool CCamera::IsExtraEntityToIgnore(CEntity *entity) {
    return plugin::CallMethodAndReturnDynGlobal<bool, CCamera *, CEntity *>(0x50CE80, this, entity);
}

bool CCamera::IsItTimeForNewcam(int CamSequence, int StartTime) {
    return plugin::CallMethodAndReturnDynGlobal<bool, CCamera *, int, int>(0x51D770, this, CamSequence, StartTime);
}

void CCamera::LerpFOV(float zoomInFactor, float zoomOutFactor, float timelimit, bool bEase) {
    plugin::CallMethodDynGlobal<CCamera *, float, float, float, bool>(0x50D280, this, zoomInFactor, zoomOutFactor, timelimit, bEase);
}

void CCamera::LoadPathSplines(int pFile) {
    plugin::CallMethodDynGlobal<CCamera *, int>(0x5B24D0, this, pFile);
}

void CCamera::Process() {
    plugin::CallMethodDynGlobal<CCamera *>(0x52B730, this);
}

void CCamera::ProcessFade() {
    plugin::CallMethodDynGlobal<CCamera *>(0x50B5D0, this);
}

void CCamera::ProcessMusicFade() {
    plugin::CallMethodDynGlobal<CCamera *>(0x50B6D0, this);
}

void CCamera::ProcessObbeCinemaCameraBoat() {
    plugin::CallMethodDynGlobal<CCamera *>(0x526E20, this);
}

void CCamera::ProcessObbeCinemaCameraCar() {
    plugin::CallMethodDynGlobal<CCamera *>(0x5267C0, this);
}

void CCamera::ProcessObbeCinemaCameraHeli() {
    plugin::CallMethodDynGlobal<CCamera *>(0x526AE0, this);
}

unsigned int CCamera::ProcessObbeCinemaCameraPed() {
    return plugin::CallMethodAndReturnDynGlobal<unsigned int, CCamera *>(0x50B880, this);
}

void CCamera::ProcessObbeCinemaCameraPlane() {
    plugin::CallMethodDynGlobal<CCamera *>(0x526C80, this);
}

void CCamera::ProcessObbeCinemaCameraTrain() {
    plugin::CallMethodDynGlobal<CCamera *>(0x526950, this);
}

void CCamera::ProcessScriptedCommands() {
    plugin::CallMethodDynGlobal<CCamera *>(0x516AE0, this);
}

void CCamera::ProcessShake(float JiggleIntensity) {
    // 0x516560
}

void CCamera::ProcessShake() {
    // 0x51A6F0
}

void CCamera::ProcessVectorMoveLinear(float ratio) {
    // 0x50D430
}

void CCamera::ProcessVectorMoveLinear() {
    // 0x5164A0
}

void CCamera::ProcessVectorTrackLinear(float ratio) {
    // 0x50D350
}

void CCamera::ProcessVectorTrackLinear() {
    // 0x516440
}

void CCamera::ProcessWideScreenOn() {
    plugin::CallMethodDynGlobal<CCamera *>(0x50B890, this);
}

void CCamera::RenderMotionBlur() {
    plugin::CallMethodDynGlobal<CCamera *>(0x50B8F0, this);
}

void CCamera::ResetDuckingSystem(CPed *ped) {
    plugin::CallMethodDynGlobal<CCamera *, CPed *>(0x50CEF0, this, ped);
}

void CCamera::Restore() {
    plugin::CallMethodDynGlobal<CCamera *>(0x50B930, this);
}

void CCamera::RestoreCameraAfterMirror() {
    plugin::CallMethodDynGlobal<CCamera *>(0x51A5A0, this);
}

void CCamera::RestoreWithJumpCut() {
    plugin::CallMethodDynGlobal<CCamera *>(0x50BAB0, this);
}

void CCamera::SetCamCutSceneOffSet(CVector const *cutsceneOffset) {
    plugin::CallMethodDynGlobal<CCamera *, CVector const *>(0x50BD20, this, cutsceneOffset);
}

void CCamera::SetCamPositionForFixedMode(CVector const *fixedModeSource, CVector const *fixedModeUpOffset) {
    plugin::CallMethodDynGlobal<CCamera *, CVector const *, CVector const *>(0x50BEC0, this, fixedModeSource, fixedModeUpOffset);
}

void CCamera::SetCameraDirectlyBehindForFollowPed_CamOnAString() {
    plugin::CallMethodDynGlobal<CCamera *>(0x50BD40, this);
}

void CCamera::SetCameraDirectlyBehindForFollowPed_ForAPed_CamOnAString(CPed *targetPed) {
    plugin::CallMethodDynGlobal<CCamera *, CPed *>(0x50BDA0, this, targetPed);
}

void CCamera::SetCameraUpForMirror() {
    plugin::CallMethodDynGlobal<CCamera *>(0x51A560, this);
}

void CCamera::SetFadeColour(unsigned char Red, unsigned char Green, unsigned char Blue) {
    plugin::CallMethodDynGlobal<CCamera *, unsigned char, unsigned char, unsigned char>(0x50BF00, this, Red, Green, Blue);
}

void CCamera::SetMotionBlur(int Red, int Green, int Blue, int value, int Blurtype) {
    plugin::CallMethodDynGlobal<CCamera *, int, int, int, int, int>(0x50BF40, this, Red, Green, Blue, value, Blurtype);
}

void CCamera::SetMotionBlurAlpha(int Alpha) {
    plugin::CallMethodDynGlobal<CCamera *, int>(0x50BF80, this, Alpha);
}

void CCamera::SetNearClipBasedOnPedCollision(float arg2) {
    plugin::CallMethodDynGlobal<CCamera *, float>(0x50CB90, this, arg2);
}

void CCamera::SetNearClipScript(float NearClip) {
    plugin::CallMethodDynGlobal<CCamera *, float>(0x50BF90, this, NearClip);
}

void CCamera::SetNewPlayerWeaponMode(short mode, short maxZoom, short minZoom) {
    plugin::CallMethodDynGlobal<CCamera *, short, short, short>(0x50BFB0, this, mode, maxZoom, minZoom);
}

void CCamera::SetParametersForScriptInterpolation(float InterpolationToStopMoving, float InterpolationToCatchUp, unsigned int TimeForInterPolation) {
    plugin::CallMethodDynGlobal<CCamera *, float, float, unsigned int>(0x50C030, this, InterpolationToStopMoving, InterpolationToCatchUp, TimeForInterPolation);
}

void CCamera::SetPercentAlongCutScene(float percent) {
    plugin::CallMethodDynGlobal<CCamera *, float>(0x50C070, this, percent);
}

void CCamera::SetRwCamera(RwCamera *rwcamera) {
    plugin::CallMethodDynGlobal<CCamera *, RwCamera *>(0x50C100, this, rwcamera);
}

void CCamera::SetWideScreenOff() {
    plugin::CallMethodDynGlobal<CCamera *>(0x50C150, this);
}

void CCamera::SetWideScreenOn() {
    plugin::CallMethodDynGlobal<CCamera *>(0x50C140, this);
}

void CCamera::SetZoomValueCamStringScript(short zoomMode) {
    plugin::CallMethodDynGlobal<CCamera *, short>(0x50C1B0, this, zoomMode);
}

void CCamera::SetZoomValueFollowPedScript(short zoomMode) {
    plugin::CallMethodDynGlobal<CCamera *, short>(0x50C160, this, zoomMode);
}

void CCamera::StartCooperativeCamMode() {
    plugin::CallMethodDynGlobal<CCamera *>(0x50C260, this);
}

void CCamera::StartTransition(short currentCamMode) {
    plugin::CallMethodDynGlobal<CCamera *, short>(0x515200, this, currentCamMode);
}

void CCamera::StartTransitionWhenNotFinishedInter(short currentCamMode) {
    plugin::CallMethodDynGlobal<CCamera *, short>(0x515BC0, this, currentCamMode);
}

void CCamera::StopCooperativeCamMode() {
    plugin::CallMethodDynGlobal<CCamera *>(0x50C270, this);
}

void CCamera::StoreValuesDuringInterPol(CVector *SourceDuringInter, CVector *TargetDuringInter, CVector *UpDuringInter, float *FOVDuringInter) {
    plugin::CallMethodDynGlobal<CCamera *, CVector *, CVector *, CVector *, float *>(0x50C290, this, SourceDuringInter, TargetDuringInter, UpDuringInter, FOVDuringInter);
}

void CCamera::TakeControl(CEntity *target, short ModeToGoTo, short TypeOfSwitch, int WhoIsInControlOfTheCamera) {
    plugin::CallMethodDynGlobal<CCamera *, CEntity *, short, short, int>(0x50C7C0, this, target, ModeToGoTo, TypeOfSwitch, WhoIsInControlOfTheCamera);
}

void CCamera::TakeControlAttachToEntity(CEntity *target, CEntity *attached, CVector *AttachedCamOffset, CVector *AttachedCamLookAt, float AttachedCamAngle, short TypeOfSwitch, int WhoIsInControlOfTheCamera) {
    plugin::CallMethodDynGlobal<CCamera *, CEntity *, CEntity *, CVector *, CVector *, float, short, int>(0x50C910, this, target, attached, AttachedCamOffset, AttachedCamLookAt, AttachedCamAngle, TypeOfSwitch, WhoIsInControlOfTheCamera);
}

void CCamera::TakeControlNoEntity(CVector const *FixedModeVector, short TypeOfSwitch, int WhoIsInControlOfTheCamera) {
    plugin::CallMethodDynGlobal<CCamera *, CVector const *, short, int>(0x50C8B0, this, FixedModeVector, TypeOfSwitch, WhoIsInControlOfTheCamera);
}

void CCamera::TakeControlWithSpline(short TypeOfSwitch) {
    plugin::CallMethodDynGlobal<CCamera *, short>(0x50CAE0, this, TypeOfSwitch);
}

bool CCamera::TryToStartNewCamMode(int CamSequence) {
    return plugin::CallMethodAndReturnDynGlobal<bool, CCamera *, int>(0x51E560, this, CamSequence);
}

void CCamera::UpdateAimingCoors(CVector const *AimingTargetCoors) {
    plugin::CallMethodDynGlobal<CCamera *, CVector const *>(0x50CB10, this, AimingTargetCoors);
}

void CCamera::UpdateSoundDistances() {
    plugin::CallMethodDynGlobal<CCamera *>(0x515BD0, this);
}

void CCamera::UpdateTargetEntity() {
    plugin::CallMethodDynGlobal<CCamera *>(0x50C360, this);
}

bool CCamera::Using1stPersonWeaponMode() {
    return plugin::CallMethodAndReturnDynGlobal<bool, CCamera *>(0x50BFF0, this);
}

void CCamera::VectorMoveLinear(CVector *MoveLinearPosnEnd, CVector *MoveLinearPosnStart, float duration, bool bMoveLinearWithEase) {
    plugin::CallMethodDynGlobal<CCamera *, CVector *, CVector *, float, bool>(0x50D160, this, MoveLinearPosnEnd, MoveLinearPosnStart, duration, bMoveLinearWithEase);
}

bool CCamera::VectorMoveRunning() {
    return plugin::CallMethodAndReturnDynGlobal<bool, CCamera *>(0x4748A0, this);
}

void CCamera::VectorTrackLinear(CVector *TrackLinearStartPoint, CVector *TrackLinearEndPoint, float duration, bool bEase) {
    plugin::CallMethodDynGlobal<CCamera *, CVector *, CVector *, float, bool>(0x50D1D0, this, TrackLinearStartPoint, TrackLinearEndPoint, duration, bEase);
}

bool CCamera::VectorTrackRunning() {
    return plugin::CallMethodAndReturnDynGlobal<bool, CCamera *>(0x474870, this);
}

void CCamera::DontProcessObbeCinemaCamera() {
    plugin::CallDynGlobal(0x50AB40);
}

void CCamera::SetCamCollisionVarDataSet(int index) {
    plugin::CallDynGlobal<int>(0x50CB60, index);
}

void CCamera::SetColVarsAimWeapon(int aimingType) {
    plugin::CallDynGlobal<int>(0x50CBF0, aimingType);
}

void CCamera::SetColVarsPed(int pedtype, int nCamPedZoom) {
    plugin::CallDynGlobal<int, int>(0x50CC50, pedtype, nCamPedZoom);
}

void CCamera::SetColVarsVehicle(int vehicletype, int CamVehicleZoom) {
    plugin::CallDynGlobal<int, int>(0x50CCA0, vehicletype, CamVehicleZoom);
}
