/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "CStreaming.h"

PLUGIN_SOURCE_FILE

unsigned int &CStreaming::ms_memoryAvailable = *reinterpret_cast<unsigned int *>(0x8A5A80);
unsigned int &CStreaming::desiredNumVehiclesLoaded = *reinterpret_cast<unsigned int *>(0x8A5A84);
bool &CStreaming::ms_bLoadVehiclesInLoadScene = *reinterpret_cast<bool *>(0x8A5A88);
int *CStreaming::ms_aDefaultCopCarModel = reinterpret_cast<int *>(0x8A5A8C);
int &CStreaming::ms_DefaultCopBikeModel = *reinterpret_cast<int *>(0x8A5A9C);
int *CStreaming::ms_aDefaultCopModel = reinterpret_cast<int *>(0x8A5AA0);
int &CStreaming::ms_DefaultCopBikerModel = *reinterpret_cast<int *>(0x8A5AB0);
signed int *CStreaming::ms_aDefaultAmbulanceModel = reinterpret_cast<signed int *>(0x8A5AB4);
signed int *CStreaming::ms_aDefaultMedicModel = reinterpret_cast<signed int *>(0x8A5AC4);
signed int *CStreaming::ms_aDefaultFireEngineModel = reinterpret_cast<signed int *>(0x8A5AD4);
signed int *CStreaming::ms_aDefaultFiremanModel = reinterpret_cast<signed int *>(0x8A5AE4);
signed int *CStreaming::ms_aDefaultCabDriverModel = reinterpret_cast<signed int *>(0x8A5AF4);
CDirectory *&CStreaming::ms_pExtraObjectsDir = *reinterpret_cast<CDirectory **>(0x8E48D0);
tStreamingFileDesc *CStreaming::ms_files = reinterpret_cast<tStreamingFileDesc *>(0x8E48D8);
bool &CStreaming::ms_bLoadingBigModel = *reinterpret_cast<bool *>(0x8E4A58);
tStreamingChannel *CStreaming::ms_channel = reinterpret_cast<tStreamingChannel *>(0x8E4A60);
signed int &CStreaming::ms_channelError = *reinterpret_cast<signed int *>(0x8E4B90);
bool &CStreaming::m_bHarvesterModelsRequested = *reinterpret_cast<bool *>(0x8E4B9C);
bool &CStreaming::m_bStreamHarvesterModelsThisFrame = *reinterpret_cast<bool *>(0x8E4B9D);
unsigned int &CStreaming::ms_numPriorityRequests = *reinterpret_cast<unsigned int *>(0x8E4BA0);
int &CStreaming::ms_lastCullZone = *reinterpret_cast<int *>(0x8E4BA4);
unsigned short &CStreaming::ms_loadedGangCars = *reinterpret_cast<unsigned short *>(0x8E4BA8);
unsigned short &CStreaming::ms_loadedGangs = *reinterpret_cast<unsigned short *>(0x8E4BAC);
unsigned int &CStreaming::ms_numPedsLoaded = *reinterpret_cast<unsigned int *>(0x8E4BB0);
unsigned int **CStreaming::ms_pedsLoaded = reinterpret_cast<unsigned int **>(0x8E4C00);
int &CStreaming::ms_currentZoneType = *reinterpret_cast<int *>(0x8E4C20);
CLoadedCarGroup &CStreaming::ms_vehiclesLoaded = *reinterpret_cast<CLoadedCarGroup *>(0x8E4C24);
CStreamingInfo *&CStreaming::ms_pEndRequestedList = *reinterpret_cast<CStreamingInfo **>(0x8E4C54);
CStreamingInfo *&CStreaming::ms_pStartRequestedList = *reinterpret_cast<CStreamingInfo **>(0x8E4C58);
CStreamingInfo *&CStreaming::ms_pEndLoadedList = *reinterpret_cast<CStreamingInfo **>(0x8E4C5C);
CStreamingInfo *&CStreaming::ms_startLoadedList = *reinterpret_cast<CStreamingInfo **>(0x8E4C60);
int &CStreaming::ms_lastImageRead = *reinterpret_cast<int *>(0x8E4C64);
signed int *CStreaming::ms_imageOffsets = reinterpret_cast<signed int *>(0x8E4C8C);
bool &CStreaming::ms_bEnableRequestListPurge = *reinterpret_cast<bool *>(0x8E4CA4);
unsigned int &CStreaming::ms_streamingBufferSize = *reinterpret_cast<unsigned int *>(0x8E4CA8);
char *&CStreaming::ms_pStreamingBuffer = *reinterpret_cast<char **>(0x8E4CAC);
unsigned int &CStreaming::ms_memoryUsed = *reinterpret_cast<unsigned int *>(0x8E4CB4);
unsigned int &CStreaming::ms_numModelsRequested = *reinterpret_cast<unsigned int *>(0x8E4CB8);
CStreamingInfo *CStreaming::ms_aInfoForModel = reinterpret_cast<CStreamingInfo *>(0x8E4CC0);
bool &CStreaming::ms_disableStreaming = *reinterpret_cast<bool *>(0x9654B0);
int &CStreaming::ms_bIsInitialised = *reinterpret_cast<int *>(0x9654B8);
bool &CStreaming::m_bBoatsNeeded = *reinterpret_cast<bool *>(0x9654BC);
bool &CStreaming::m_bLoadingScene = *reinterpret_cast<bool *>(0x9654BD);
bool &CStreaming::m_bCopBikeLoaded = *reinterpret_cast<bool *>(0x9654BE);
bool &CStreaming::m_bDisableCopBikes = *reinterpret_cast<bool *>(0x9654BF);
CLinkList<CEntity*> &CStreaming::ms_rwObjectInstances = *reinterpret_cast<CLinkList<CEntity*> *>(0x9654F0);
RwStream &gRwStream = *reinterpret_cast<RwStream *>(0x8E48AC);

void *CStreaming::AddEntity(CEntity *a2) {
    return plugin::CallAndReturnDynGlobal<void *, CEntity *>(0x409650, a2);
}

int CStreaming::AddImageToList(char const *lpFileName, bool bNotPlayerImg) {
    return plugin::CallAndReturnDynGlobal<int, char const *, bool>(0x407610, lpFileName, bNotPlayerImg);
}

void CStreaming::AddLodsToRequestList(CVector const *Posn, unsigned int Streamingflags) {
    plugin::CallDynGlobal<CVector const *, unsigned int>(0x40C520, Posn, Streamingflags);
}

void CStreaming::AddModelsToRequestList(CVector const *posn, unsigned int StreamingFlags) {
    plugin::CallDynGlobal<CVector const *, unsigned int>(0x40D3F0, posn, StreamingFlags);
}

bool CStreaming::AddToLoadedVehiclesList() {
    return plugin::CallAndReturnDynGlobal<bool>(0x408000);
}

bool CStreaming::AreAnimsUsedByRequestedModels(int AnimFileIndex) {
    return plugin::CallAndReturnDynGlobal<bool, int>(0x407AD0, AnimFileIndex);
}

bool CStreaming::AreTexturesUsedByRequestedModels(int txdIndex) {
    return plugin::CallAndReturnDynGlobal<bool, int>(0x409A90, txdIndex);
}

void CStreaming::ClearFlagForAll(unsigned int eStreamingFlag) {
    plugin::CallDynGlobal<unsigned int>(0x407A40, eStreamingFlag);
}

void CStreaming::ClearSlots(int NumOfSlots) {
    plugin::CallDynGlobal<int>(0x40BAA0, NumOfSlots);
}

char CStreaming::ConvertBufferToObject(char *pFileContect, int index, int ChannelIndex) {
    return plugin::CallAndReturnDynGlobal<char, char *, int, int>(0x40C6B0, pFileContect, index, ChannelIndex);
}

void CStreaming::DeleteAllRwObjects() {
    plugin::CallDynGlobal(0x4090A0);
}

bool CStreaming::DeleteLeastUsedEntityRwObject(bool bNotOnScreen, unsigned int StreamingFlags) {
    return plugin::CallAndReturnDynGlobal<bool, bool, unsigned int>(0x409760, bNotOnScreen, StreamingFlags);
}

void CStreaming::DeleteRwObjectsAfterDeath(CVector const *PlayerPosn) {
    plugin::CallDynGlobal<CVector const *>(0x409210, PlayerPosn);
}

void CStreaming::DeleteRwObjectsBehindCamera(int memoryToCleanInBytes) {
    plugin::CallDynGlobal<int>(0x40D7C0, memoryToCleanInBytes);
}

bool CStreaming::DeleteRwObjectsBehindCameraInSectorList(CPtrList *List, int memoryToCleanInBytes) {
    return plugin::CallAndReturnDynGlobal<bool, CPtrList *, int>(0x409940, List, memoryToCleanInBytes);
}

void CStreaming::DeleteRwObjectsInSectorList(CPtrList *PtrList, int arg2, int arg3) {
    plugin::CallDynGlobal<CPtrList *, int, int>(0x407A70, PtrList, arg2, arg3);
}

char CStreaming::DeleteRwObjectsNotInFrustumInSectorList(CPtrList *List, int memoryToCleanInBytes) {
    return plugin::CallAndReturnDynGlobal<char, CPtrList *, int>(0x4099E0, List, memoryToCleanInBytes);
}

void CStreaming::DisableCopBikes(bool bDisable) {
    plugin::CallDynGlobal<bool>(0x407D10, bDisable);
}

int CStreaming::FindMIPedSlotForInterior(int RandFactor) {
    return plugin::CallAndReturnDynGlobal<int, int>(0x407FB0, RandFactor);
}

bool CStreaming::FinishLoadingLargeFile(char *FileName, int modelIndex) {
    return plugin::CallAndReturnDynGlobal<bool, char *, int>(0x408CB0, FileName, modelIndex);
}

bool CStreaming::FlushChannels() {
    return plugin::CallAndReturnDynGlobal<bool>(0x40E460);
}

bool CStreaming::FlushRequestList() {
    return plugin::CallAndReturnDynGlobal<bool>(0x40E4E0);
}

void CStreaming::ForceLayerToRead(int arg1) {
    plugin::CallDynGlobal<int>(0x407A10, arg1);
}

int CStreaming::GetDefaultCabDriverModel() {
    return plugin::CallAndReturnDynGlobal<int>(0x407D50);
}

int CStreaming::GetDefaultCopCarModel(unsigned int bIncludeCopBike) {
    return plugin::CallAndReturnDynGlobal<int, unsigned int>(0x407C50, bIncludeCopBike);
}

int CStreaming::GetDefaultCopModel() {
    return plugin::CallAndReturnDynGlobal<int>(0x407C00);
}

int CStreaming::GetDefaultFiremanModel() {
    return plugin::CallAndReturnDynGlobal<int>(0x407D40);
}

int CStreaming::GetDefaultMedicModel() {
    return plugin::CallAndReturnDynGlobal<int>(0x407D20);
}

signed int CStreaming::GetDiscInDrive() {
    return plugin::CallAndReturnDynGlobal<signed int>(0x40E9B0);
}

int CStreaming::GetNextFileOnCd(int pos, bool bNotPriority) {
    return plugin::CallAndReturnDynGlobal<int, int, bool>(0x408E20, pos, bNotPriority);
}

bool CStreaming::HasSpecialCharLoaded(int slot) {
    return plugin::CallAndReturnDynGlobal<bool, int>(0x407F00, slot);
}

bool CStreaming::HasVehicleUpgradeLoaded(int ModelIndex) {
    return plugin::CallAndReturnDynGlobal<bool, int>(0x407820, ModelIndex);
}

void CStreaming::IHaveUsedStreamingMemory() {
    plugin::CallDynGlobal(0x407BF0);
}

void CStreaming::ImGonnaUseStreamingMemory() {
    plugin::CallDynGlobal(0x407BE0);
}

void CStreaming::Init() {
    plugin::CallDynGlobal(0x5B9020);
}

void CStreaming::Init2() {
    plugin::CallDynGlobal(0x5B8AD0);
}

void CStreaming::InitImageList() {
    plugin::CallDynGlobal(0x4083C0);
}

void CStreaming::InstanceLoadedModels(CVector const *posn) {
    plugin::CallDynGlobal<CVector const *>(0x4084F0, posn);
}

bool CStreaming::IsCarModelNeededInCurrentZone(int VehicleModelIndex) {
    return plugin::CallAndReturnDynGlobal<bool, int>(0x407DD0, VehicleModelIndex);
}

bool CStreaming::IsInitialised() {
    return plugin::CallAndReturnDynGlobal<bool>(0x407600);
}

bool CStreaming::IsObjectInCdImage(int ModelInex) {
    return plugin::CallAndReturnDynGlobal<bool, int>(0x407800, ModelInex);
}

bool CStreaming::IsVeryBusy() {
    return plugin::CallAndReturnDynGlobal<bool>(0x4076A0);
}

void CStreaming::Load() {
    plugin::CallDynGlobal(0x5D29E0);
}

void CStreaming::LoadAllRequestedModels(bool bOnlyPriorityRequests) {
    plugin::CallDynGlobal<bool>(0x40EA10, bOnlyPriorityRequests);
}

void CStreaming::LoadCdDirectory(char const *ArchiveName, int archiveID) {
    // 0x5B6170
}

void CStreaming::LoadCdDirectory() {
    // 0x5B82C0
}

void CStreaming::LoadInitialPeds() {
    plugin::CallDynGlobal(0x40D3D0);
}

void CStreaming::LoadInitialVehicles() {
    plugin::CallDynGlobal(0x407F20);
}

void CStreaming::LoadInitialWeapons() {
    plugin::CallDynGlobal(0x40A120);
}

void CStreaming::LoadRequestedModels() {
    plugin::CallDynGlobal(0x40E3A0);
}

void CStreaming::LoadScene(CVector const *Posn) {
    plugin::CallDynGlobal<CVector const *>(0x40EB70, Posn);
}

void CStreaming::LoadSceneCollision(CVector const *Posn) {
    plugin::CallDynGlobal<CVector const *>(0x40ED80, Posn);
}

void CStreaming::LoadZoneVehicle(CVector const *posn) {
    plugin::CallDynGlobal<CVector const *>(0x40B4B0, posn);
}

void CStreaming::MakeSpaceFor(int memoryToCleanInBytes) {
    plugin::CallDynGlobal<int>(0x40E120, memoryToCleanInBytes);
}

void CStreaming::PossiblyStreamCarOutAfterCreation(int modelId) {
    plugin::CallDynGlobal<int>(0x40BA70, modelId);
}

void CStreaming::ProcessEntitiesInSectorList(CPtrList *list, float posn_x, float posn_y, float min_posn_x, float min_posn_y, float max_posn_x, float max_posn_y, float distance, unsigned int Streamingflags) {
    // 0x40C270
}

void CStreaming::ProcessEntitiesInSectorList(CPtrList *list, unsigned int streamingFlags) {
    // 0x40C450
}

bool CStreaming::ProcessLoadingChannel(int channelIndex) {
    return plugin::CallAndReturnDynGlobal<bool, int>(0x40E170, channelIndex);
}

void CStreaming::PurgeRequestList() {
    plugin::CallDynGlobal(0x40C1E0);
}

unsigned int CStreaming::ReInit() {
    return plugin::CallAndReturnDynGlobal<unsigned int>(0x40E560);
}

void CStreaming::ReadIniFile() {
    plugin::CallDynGlobal(0x5BCCD0);
}

void CStreaming::ReclassifyLoadedCars() {
    plugin::CallDynGlobal(0x40AFA0);
}

void CStreaming::RemoveAllUnusedModels() {
    plugin::CallDynGlobal(0x40CF80);
}

void CStreaming::RemoveBigBuildings() {
    plugin::CallDynGlobal(0x4093B0);
}

void CStreaming::RemoveBuildingsNotInArea(int AreaCode) {
    plugin::CallDynGlobal<int>(0x4094B0, AreaCode);
}

void CStreaming::RemoveCarModel(int modelIndex) {
    plugin::CallDynGlobal<int>(0x4080F0, modelIndex);
}

void CStreaming::RemoveCurrentZonesModels() {
    plugin::CallDynGlobal(0x40B080);
}

void CStreaming::RemoveDodgyPedsFromRandomSlots() {
    plugin::CallDynGlobal(0x40BE60);
}

void CStreaming::RemoveEntity(CLink<CEntity*> *streamingLink) {
    plugin::CallDynGlobal<CLink<CEntity*> *>(0x409710, streamingLink);
}

void CStreaming::RemoveInappropriatePedModels() {
    plugin::CallDynGlobal(0x40B3A0);
}

bool CStreaming::RemoveLeastUsedModel(unsigned int StreamingFlags) {
    return plugin::CallAndReturnDynGlobal<bool, unsigned int>(0x40CFD0, StreamingFlags);
}

bool CStreaming::RemoveLoadedVehicle() {
    return plugin::CallAndReturnDynGlobal<bool>(0x40C020);
}

bool CStreaming::RemoveLoadedZoneModel() {
    return plugin::CallAndReturnDynGlobal<bool>(0x40B340);
}

void CStreaming::RemoveModel(int Modelindex) {
    plugin::CallDynGlobal<int>(0x4089A0, Modelindex);
}

unsigned int CStreaming::RemoveUnusedModelsInLoadedList() {
    return plugin::CallAndReturnDynGlobal<unsigned int>(0x407AC0);
}

void CStreaming::RenderEntity(CLink<CEntity*> *streamingLink) {
    plugin::CallDynGlobal<CLink<CEntity*> *>(0x4096D0, streamingLink);
}

void CStreaming::RequestBigBuildings(CVector const *posn) {
    plugin::CallDynGlobal<CVector const *>(0x409430, posn);
}

void CStreaming::RequestFile(int index, int offset, int size, int imgId, int streamingFlags) {
    plugin::CallDynGlobal<int, int, int, int, int>(0x40A080, index, offset, size, imgId, streamingFlags);
}

void CStreaming::RequestFilesInChannel(int channelId) {
    plugin::CallDynGlobal<int>(0x409050, channelId);
}

void CStreaming::RequestModel(int dwModelId, int Streamingflags) {
    plugin::CallDynGlobal<int, int>(0x4087E0, dwModelId, Streamingflags);
}

void CStreaming::RequestModelStream(int streamNum) {
    plugin::CallDynGlobal<int>(0x40CBA0, streamNum);
}

void CStreaming::RequestPlayerSection(int modelIndex, char const *string, int streamingFlags) {
    plugin::CallDynGlobal<int, char const *, int>(0x409FF0, modelIndex, string, streamingFlags);
}

void CStreaming::RequestSpecialChar(int slot, char const *Name, int streamingFlags) {
    plugin::CallDynGlobal<int, char const *, int>(0x40B450, slot, Name, streamingFlags);
}

void CStreaming::RequestSpecialModel(int slot, char *name, int StreamingFlags) {
    plugin::CallDynGlobal<int, char *, int>(0x409D10, slot, name, StreamingFlags);
}

void CStreaming::RequestTxdModel(int TxdModelID, int Streamingflags) {
    plugin::CallDynGlobal<int, int>(0x407100, TxdModelID, Streamingflags);
}

void CStreaming::RequestVehicleUpgrade(int modelIndex, int StreamingFlags) {
    plugin::CallDynGlobal<int, int>(0x408C70, modelIndex, StreamingFlags);
}

void CStreaming::RetryLoadFile(int streamNum) {
    plugin::CallDynGlobal<int>(0x4076C0, streamNum);
}

void CStreaming::Save() {
    plugin::CallDynGlobal(0x5D29A0);
}

void CStreaming::SetLoadVehiclesInLoadScene(bool bEnable) {
    plugin::CallDynGlobal<bool>(0x407A30, bEnable);
}

void CStreaming::SetMissionDoesntRequireAnim(int slot) {
    plugin::CallDynGlobal<int>(0x48B570, slot);
}

void CStreaming::SetMissionDoesntRequireModel(int modelIndex) {
    plugin::CallDynGlobal<int>(0x409C90, modelIndex);
}

void CStreaming::SetMissionDoesntRequireSpecialChar(int slot) {
    plugin::CallDynGlobal<int>(0x40B490, slot);
}

void CStreaming::SetModelIsDeletable(int modelIndex) {
    plugin::CallDynGlobal<int>(0x409C10, modelIndex);
}

void CStreaming::SetModelTxdIsDeletable(int modelIndex) {
    plugin::CallDynGlobal<int>(0x409C70, modelIndex);
}

void CStreaming::SetSpecialCharIsDeletable(int slot) {
    plugin::CallDynGlobal<int>(0x40B470, slot);
}

void CStreaming::Shutdown() {
    plugin::CallDynGlobal(0x4084B0);
}

void CStreaming::StartRenderEntities() {
    plugin::CallDynGlobal(0x4096C0);
}

bool CStreaming::StreamAmbulanceAndMedic(bool bStreamForAccident) {
    return plugin::CallAndReturnDynGlobal<bool, bool>(0x40A2A0, bStreamForAccident);
}

void CStreaming::StreamCopModels(int townID) {
    plugin::CallDynGlobal<int>(0x40A150, townID);
}

bool CStreaming::StreamFireEngineAndFireman(bool bStreamForFire) {
    return plugin::CallAndReturnDynGlobal<bool, bool>(0x40A400, bStreamForFire);
}

void CStreaming::StreamOneNewCar() {
    plugin::CallDynGlobal(0x40B4F0);
}

void CStreaming::StreamPedsForInterior(int interiorType) {
    plugin::CallDynGlobal<int>(0x40BBB0, interiorType);
}

void CStreaming::StreamPedsIntoRandomSlots(int *pModelID) {
    plugin::CallDynGlobal<int *>(0x40BDA0, pModelID);
}

void CStreaming::StreamVehiclesAndPeds() {
    plugin::CallDynGlobal(0x40B700);
}

void CStreaming::StreamVehiclesAndPeds_Always(CVector const *posn) {
    plugin::CallDynGlobal<CVector const *>(0x40B650, posn);
}

void CStreaming::StreamZoneModels(CVector const *posn) {
    plugin::CallDynGlobal<CVector const *>(0x40A560, posn);
}

void CStreaming::StreamZoneModels_Gangs(CVector const *unused) {
    plugin::CallDynGlobal<CVector const *>(0x40AA10, unused);
}

void CStreaming::Update() {
    plugin::CallDynGlobal(0x40E670);
}

void CStreaming::UpdateForAnimViewer() {
    plugin::CallDynGlobal(0x40E960);
}

bool CStreaming::WeAreTryingToPhaseVehicleOut(int modelIndex) {
    return plugin::CallAndReturnDynGlobal<bool, int>(0x407F80, modelIndex);
}
