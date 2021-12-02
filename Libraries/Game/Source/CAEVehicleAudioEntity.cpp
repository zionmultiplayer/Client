/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "CAEVehicleAudioEntity.h"

PLUGIN_SOURCE_FILE

CPed *&CAEVehicleAudioEntity::s_pPlayerAttachedForRadio = *reinterpret_cast<CPed **>(0xB6B98C);
CPed *&CAEVehicleAudioEntity::s_pPlayerDriver = *reinterpret_cast<CPed **>(0xB6B990);
bool &CAEVehicleAudioEntity::s_HelicoptorsDisabled = *reinterpret_cast<bool *>(0xB6B994);
short &CAEVehicleAudioEntity::s_NextDummyEngineSlot = *reinterpret_cast<short *>(0xB6B998);
tVehicleAudioSettings *&CAEVehicleAudioEntity::s_pVehicleAudioSettingsForRadio = *reinterpret_cast<tVehicleAudioSettings **>(0xB6B99C);
tEngineDummySlot(&CAEVehicleAudioEntity::s_DummyEngineSlots)[10] = *reinterpret_cast<tEngineDummySlot(*)[10]>(0xB6B9A0);
tVehicleAudioSettings const(&gVehicleAudioSettings)[232] = *reinterpret_cast<tVehicleAudioSettings const(*)[232]>(0x860AF0);
