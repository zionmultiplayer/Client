#include "Zion/RPCs.hh"
#include "Zion/Client.hh"
#include "Zion/Cursor.hh"
#include "Zion/ChatWindow.hh"
#include "Zion/LocalPlayer.hh"
#include "Zion/SpawnScreen.hh"
#include "Zion/Util.hh"
#include "Zion/Dialog.hh"
#include "Zion/TextDraw.hh"
#include "Zion/Log.hh"
#include "Zion/Main.hh"
#include "Game/CClock.h"
#include "Game/CWeather.h"
#include "Game/CHud.h"
#include "Game/CStreaming.h"
#include "Game/CMessages.h"
#include "Game/CTimer.h"
#include "Game/CWorld.h"
#include "Game/CCamera.h"
#include "Game/CExplosion.h"
#include "Game/CCarEnterExit.h"
#include "Game/CCarCtrl.h"
#include "RakNet/SAMP/SAMP.h"
#include "RakNet/StringCompressor.h"

#define player Zion::Main::player
#define pad Zion::Main::pad

static Zion::Player::SpawnData spawnData;

static void InitGame(RPCParameters *parms)
{
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);

    bool zoneNames;
    bool useCJAnims;
    bool allowInteriorWeapons;
    bool limitGlobalChatRadius;
    float globalChatRadius;
    bool stuntBonus;
    float nameTagDrawDistance;
    bool disableEnterExits;
    bool nameTagLOS;
    bool manualVehicleEngineAndLight;
    bool showPlayerTags;
    int showPlayerMarkers;
    unsigned char worldTime;
    unsigned char weather;
    float gravity;
    bool lanMode;
    int deathDropMoney;
    bool instagib;
    int lagCompensation;
    int vehicleFriendlyFire;
    unsigned char serverNameLength;
    char serverName[256];

    bitStream.ReadCompressed<bool>(zoneNames);
    bitStream.ReadCompressed<bool>(useCJAnims);
    bitStream.ReadCompressed<bool>(allowInteriorWeapons);
    bitStream.ReadCompressed<bool>(limitGlobalChatRadius);
    bitStream.Read<float>(globalChatRadius);
    bitStream.ReadCompressed<bool>(stuntBonus);
    bitStream.Read<float>(nameTagDrawDistance);
    bitStream.ReadCompressed<bool>(disableEnterExits);
    bitStream.ReadCompressed<bool>(nameTagLOS);
    bitStream.ReadCompressed<bool>(manualVehicleEngineAndLight);
    bitStream.Read<int>(Zion::Client::classesAvalible);
    bitStream.Read<unsigned short>(Zion::Client::id);
    bitStream.ReadCompressed<bool>(showPlayerTags);
    bitStream.Read<int>(showPlayerMarkers);
    bitStream.Read<unsigned char>(worldTime);
    bitStream.Read<unsigned char>(weather);
    bitStream.Read<float>(gravity);
    bitStream.ReadCompressed<bool>(lanMode);
    bitStream.Read<int>(deathDropMoney);
    bitStream.ReadCompressed<bool>(instagib);
    bitStream.Read<int>(Zion::Client::onFootSendRate);
    bitStream.Read<int>(Zion::Client::inCarSendRate);
    bitStream.IgnoreBits(BYTES_TO_BITS(sizeof(int))); // Firing send rate
    bitStream.IgnoreBits(BYTES_TO_BITS(sizeof(int))); // Send multiplier
    bitStream.Read<int>(lagCompensation);
    bitStream.Read<unsigned char>(serverNameLength);
    bitStream.Read(serverName, serverNameLength);
    bitStream.IgnoreBits(BYTES_TO_BITS(212)); // vehicles
    bitStream.Read<int>(vehicleFriendlyFire);

    CWeather::ForceWeatherNow(weather);
    CClock::ms_nGameClockHours = worldTime;
    CClock::ms_nGameClockMinutes = 0;

    // CGame::gravity
    *(float *)0x863984 = gravity;

    Zion::Client::state = Zion::Client::State::Connected;
    Zion::Client::RequestClass(0);
    Zion::SpawnScreen::show = true;
}

static void RequestClass(RPCParameters *parms)
{
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);

    unsigned char response;
    Zion::Player::SpawnData spawnData;

    bitStream.Read<unsigned char>(response);
    bitStream.Read<Zion::Player::SpawnData>(spawnData);

    if(response)
        ::spawnData = spawnData;

    if(CStreaming::HasModelLoaded(spawnData.skin) == false)
    {
        CStreaming::RequestModel(spawnData.skin, 0);
        CStreaming::LoadAllRequestedModels(false);
    }

    player->SetModelIndex(spawnData.skin);
}

static void RequestSpawn(RPCParameters *parms)
{
    if(*(unsigned char *)parms->input)
    {
        if(CStreaming::HasModelLoaded(spawnData.skin) == false)
        {
            CStreaming::RequestModel(spawnData.skin, 0);
            CStreaming::LoadAllRequestedModels(false);
        }

        player->SetModelIndex(spawnData.skin);
        player->SetPosn(spawnData.position);
        player->m_fAimingRotation = Zion::Util::DegressToRadians(spawnData.rotation);
        player->m_fCurrentRotation = Zion::Util::DegressToRadians(spawnData.rotation);

        TheCamera.SetCameraDirectlyBehindForFollowPed_CamOnAString();
        TheCamera.RestoreWithJumpCut();

        Zion::Client::SendSpawn();
    }
}

static void SetPlayerInterior(RPCParameters *parms)
{
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);

    unsigned char interior;
    bitStream.Read<unsigned char>(interior);

    // CGame::currArea
    *(int *)0xB72914 = interior;
    player->m_nAreaCode = interior;
    CStreaming::RemoveBuildingsNotInArea(interior);
}

static void ToggleClock(RPCParameters *parms)
{
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);

    unsigned char toggle;
    bitStream.Read<unsigned char>(toggle);

    CHud::bDrawClock = toggle;
}

static void SetPlayerPosition(RPCParameters *parms)
{
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);

    Zion::Vector3F position;
    bitStream.Read<Zion::Vector3F>(position);

    player->SetPosn(position);
}

static void SetPlayerFacingAngle(RPCParameters *parms)
{
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);

    float rotation;
    bitStream.Read<float>(rotation);

    player->m_fAimingRotation = Zion::Util::DegressToRadians(rotation);
    player->m_fCurrentRotation = Zion::Util::DegressToRadians(rotation);
}

static void SetPlayerCameraPosition(RPCParameters *parms)
{
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);

    Zion::Vector3F position;
    bitStream.Read<Zion::Vector3F>(position);

    CVector fixedModeSource = CVector(position.x, position.y, position.z);
    CVector fixedModeUpOffset = CVector(0.0F, 0.0F, 0.0F);
    TheCamera.SetCamPositionForFixedMode(&fixedModeSource, &fixedModeUpOffset);
}

static void SetPlayerCameraLookAt(RPCParameters *parms)
{
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);

    Zion::Vector3F lookAt;
    bitStream.Read<Zion::Vector3F>(lookAt);

    CVector fixedModeVector = lookAt;
    TheCamera.TakeControlNoEntity(&fixedModeVector, SWITCHTYPE_JUMPCUT, 1);
}

static void ServerJoin(RPCParameters *parms) {
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);

    unsigned short id;
    unsigned char nicknameLength;
    char nickname[32];

    bitStream.Read<unsigned short>(id);
    bitStream.IgnoreBits(32); // Padding
    bitStream.IgnoreBits(8); // Is NPC
    bitStream.Read<unsigned char>(nicknameLength);
    bitStream.Read(nickname, nicknameLength);
    nickname[nicknameLength] = 0;

    while(Zion::Client::players.GetLength() <= id)
        Zion::Client::players.Push(nullptr);

    Zion::Client::players[id] = Zion::RemotePlayer::CreateRemotePlayer(nickname, id);
}

static void WorldPlayerAdd(RPCParameters *parms)
{
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);

    unsigned short id;
    unsigned char team;
    int skin;
    Zion::Vector3F position;
    float rotation;
    unsigned int color;
    unsigned char fightingStyle;

    bitStream.Read<unsigned short>(id);
    bitStream.Read<unsigned char>(team);
    bitStream.Read<int>(skin);
    bitStream.Read<Zion::Vector3F>(position);
    bitStream.Read<float>(rotation);
    bitStream.Read<unsigned int>(color);
    bitStream.Read<unsigned char>(fightingStyle);

    if(id < Zion::Client::players.GetLength()) {
        Zion::RemotePlayer *remotePlayer = Zion::Client::players[id];
        if(remotePlayer != nullptr)
        {
            remotePlayer->Spawn(skin, position, rotation);
            remotePlayer->color = color;
            remotePlayer->ped->m_nFightingStyle = fightingStyle;
        }
    }
}

static void WorldVehicleAdd(RPCParameters *parms)
{
    static CPool<CVehicle, CHeli> *&vehiclePool = *(CPool<CVehicle, CHeli> **)0xB74494;
    
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);

    struct NV {
        unsigned short      index;
        int                 model;
        Zion::Vector3F      position;
        float               rotation;
        unsigned char       aColor1;
        unsigned char       aColor2;
        float               health;
        unsigned char       interior;
        unsigned int        doorDamageStatus;
        unsigned int        panelDamageStatus;
        unsigned char       lightDamageStatus;
        unsigned char       tireDamageStatus;
        unsigned char       addSiren;
        unsigned char       modSlots[14];
        unsigned char       paintjob;
        unsigned int        cColor1;
        unsigned int        cColor2;
        unsigned char       unknown;
    } __attribute__((packed)) nv;

    bitStream.Read<NV>(nv);

    if(nv.model < 400 || nv.model > 611)
        return;

    if(CStreaming::HasModelLoaded(nv.model) == false)
    {
        CStreaming::RequestModel(nv.model, GAME_REQUIRED);
        CStreaming::LoadAllRequestedModels(false);
    }

    CVehicle *vehicle = CCarCtrl::CreateCarForScript(nv.model, nv.position, 0);
    vehicle->m_nAreaCode = 0;
    vehicle->m_nDoorLock = CARLOCK_UNLOCKED;
    vehicle->m_nPrimaryColor = nv.cColor1;
    vehicle->m_nSecondaryColor = nv.cColor2;
    vehicle->m_fHealth = nv.health;
    vehicle->SetHeading(Zion::Util::DegressToRadians(nv.rotation));
    vehicle->SetPosn(nv.position.x, nv.position.y, nv.position.z + 0.1F);

    // CPool_CVehicle__handleOf
    ((int (__thiscall *)(void *, CVehicle *))0x424160)(vehiclePool, vehicle);
    
    while(Zion::Client::vehicles.GetLength() <= nv.index)
        Zion::Client::vehicles.Push(nullptr);

    Zion::Client::vehicles[nv.index] = vehicle;
}

static void ShowTextDraw(RPCParameters *parms)
{
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);

    unsigned short id;
    Zion::TextDraw::Transmit t;
    unsigned short stringLength;
    char string[256];

    bitStream.Read<unsigned short>(id);
    bitStream.Read<Zion::TextDraw::Transmit>(t);
    bitStream.Read<unsigned short>(stringLength);
    bitStream.Read(string, stringLength);
    string[stringLength] = 0;

    Zion::TextDraw::Add(t, id);
    Zion::TextDraw::SetString_(id, string);
}

static void TextDrawHide(RPCParameters *parms)
{
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);

    unsigned short id;
    bitStream.Read<unsigned short>(id);

    Zion::TextDraw::Remove(id);
}

static void TextDrawSetString(RPCParameters *parms)
{
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);

    unsigned short id;
    unsigned short stringLength;
    char string[256];

    bitStream.Read<unsigned short>(id);
    bitStream.Read<unsigned short>(stringLength);
    bitStream.Read(string, stringLength);
    string[stringLength] = 0;

    Zion::TextDraw::SetString_(id, string);
}

static void ShowDialog(RPCParameters *parms)
{
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);

    unsigned char titleLength;
    unsigned char button1Length;
    unsigned char button2Length;
    
    bitStream.Read<unsigned short>(Zion::Dialog::id);
    bitStream.Read<unsigned char>(Zion::Dialog::style);

    bitStream.Read<unsigned char>(titleLength);
    bitStream.Read(Zion::Dialog::title, titleLength);
    Zion::Dialog::title[titleLength] = 0;

    bitStream.Read<unsigned char>(button1Length);
    bitStream.Read(Zion::Dialog::button1, button1Length);
    Zion::Dialog::button1[button1Length] = 0;

    bitStream.Read<unsigned char>(button2Length);
    bitStream.Read(Zion::Dialog::button2, button2Length);
    Zion::Dialog::button2[button2Length] = 0;

    stringCompressor->DecodeString(Zion::Dialog::info, 512, &bitStream);

    Zion::Dialog::Open();
}

static void ClickTextDraw(RPCParameters *parms)
{
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);

    bool x;
    unsigned int hoverColor;

    bitStream.Read<bool>(x);
    bitStream.Read<unsigned int>(hoverColor);
    
    Zion::TextDraw::SelectTextDraw(x);
    Zion::TextDraw::SetHoverColor(hoverColor);
}

static void CreateExplosion(RPCParameters *parms)
{
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);

    Zion::Vector3F position;
    int type;
    float radius;

    bitStream.Read<Zion::Vector3F>(position);
    bitStream.Read<int>(type);
    bitStream.Read<float>(radius);

    CExplosion::AddExplosion(
        nullptr, nullptr, (eExplosionType)type, CVector(position.x, position.y, position.z), 3000, true, 0.0F, 0);
}

static void EnableStuntBonusForPlayer(RPCParameters *parms)
{
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);

    unsigned char enable;
    bitStream.Read<unsigned char>(enable);

    *(unsigned int *)0xA4A474 = enable;
}

static void SetPlayerPositionFindZ(RPCParameters *parms)
{
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);

    Zion::Vector3F position;
    bitStream.Read<Zion::Vector3F>(position);
    
    player->SetPosn(
        position.x, position.y, CWorld::FindGroundZForCoord(position.x, position.y));
}

static void SetPlayerHealth(RPCParameters *parms)
{
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);

    bitStream.Read<float>(player->m_fHealth);
}

static void SetPlayerArmour(RPCParameters *parms)
{
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);

    bitStream.Read<float>(player->m_fArmour);
}

static void SetPlayerAmmo(RPCParameters *parms)
{
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);

    float ammo;
    bitStream.Read<float>(ammo);

    player->m_aWeapons[player->m_nActiveWeaponSlot].m_nTotalAmmo = ammo;
}

static void SetPlayerDrunkLevel(RPCParameters *parms)
{
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);

    int level;
    bitStream.Read<int>(level);

    player->m_pPlayerData->m_nDrunkenness = level;
}

static char gameText[256];

static void DisplayGameText(RPCParameters *parms)
{
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);

    int style;
    int time;
    int textLength;

    bitStream.Read<int>(style);
    bitStream.Read<int>(time);
    bitStream.Read<int>(textLength);
    bitStream.Read(gameText, textLength);
    gameText[textLength] = 0;

    CMessages::ClearMessages(false);
    CMessages::AddBigMessage(gameText, time, style);
}

static void PutPlayerInVehicle(RPCParameters *parms)
{
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);

    unsigned short vehicleId;
    unsigned char seat;

    bitStream.Read<unsigned short>(vehicleId);
    bitStream.Read<unsigned char>(seat);

    if(vehicleId >= Zion::Client::vehicles.GetLength())
        return;

    CVehicle *vehicle = Zion::Client::vehicles[vehicleId];
    if(vehicle != nullptr)
    {
        if(seat == 0)
            CCarEnterExit::SetPedInCarDirect(player, vehicle, 0, true);
        else
            CCarEnterExit::SetPedInCarDirect(player, vehicle, seat, false);
    }
}

static void SetGravity(RPCParameters *parms)
{
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);
    
    float gravity;
    bitStream.Read<float>(gravity);

    // CGame::gravity
    *(float *)0x863984 = gravity;
}

static void ForceClassSelection(RPCParameters *parms)
{
    Zion::SpawnScreen::show = true;
    Zion::Client::RequestClass(0);
}

static void SetPlayerFightingStyle(RPCParameters *parms)
{
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);

    unsigned short playerId;
    unsigned char fightingStyle;

    bitStream.Read<unsigned short>(playerId);
    bitStream.Read<unsigned char>(fightingStyle);

    if(playerId == Zion::Client::id)
        player->m_nFightingStyle = fightingStyle;
    else
    {
        if(playerId >= Zion::Client::players.GetLength())
            return;

        Zion::RemotePlayer *remotePlayer = Zion::Client::players[playerId];
        if(remotePlayer == nullptr)
            return;

        remotePlayer->ped->m_nFightingStyle = fightingStyle;
    }
}

static void SetPlayerSkin(RPCParameters *parms)
{
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);

    int playerId;
    unsigned int skin;

    bitStream.Read<int>(playerId);
    bitStream.Read<unsigned int>(skin);

    if(CStreaming::HasModelLoaded(skin) == false)
    {
        CStreaming::RequestModel(skin, 0);
        CStreaming::LoadAllRequestedModels(false);
    }

    if(playerId == Zion::Client::id)
        player->SetModelIndex(skin);
    else
    {
        if(playerId >= Zion::Client::players.GetLength())
            return;

        Zion::RemotePlayer *remotePlayer = Zion::Client::players[playerId];
        if(remotePlayer == nullptr)
            return;

        remotePlayer->ped->SetModelIndex(skin);
    }
}

static void SetSpawnInfo(RPCParameters *parms)
{
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);

    bitStream.Read<Zion::Player::SpawnData>(spawnData);
}

static void SetPlayerName(RPCParameters *parms)
{
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);

    unsigned short playerId;
    unsigned char nameLength;
    char name[36];
    unsigned char sucess;

    bitStream.Read<unsigned short>(playerId);
    bitStream.Read<unsigned char>(nameLength);
    bitStream.Read(name, nameLength);
    name[nameLength] = 0;
    bitStream.Read<unsigned char>(sucess);

    if(sucess == 1)
    {
        if(playerId >= Zion::Client::players.GetLength())
            return;

        Zion::RemotePlayer *remotePlayer = Zion::Client::players[playerId];
        if(remotePlayer == nullptr)
            return;

        strncpy(remotePlayer->nickname, name, 32);
    }
}

static void SetCameraBehindPlayer(RPCParameters *parms)
{
    TheCamera.SetCameraDirectlyBehindForFollowPed_CamOnAString();
    TheCamera.RestoreWithJumpCut();
}

static void SetVehicleParamsForPlayer(RPCParameters *parms)
{
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);

    unsigned short vehicleId;
    unsigned char objective;
    unsigned char doorsLocked;

    bitStream.Read<unsigned short>(vehicleId);
    bitStream.Read<unsigned char>(objective);
    bitStream.Read<unsigned char>(doorsLocked);

    if(vehicleId >= Zion::Client::vehicles.GetLength())
        return;

    CVehicle *vehicle = Zion::Client::vehicles[vehicleId];
    if(vehicle == nullptr)
        return;

    vehicle->m_nDoorLock = doorsLocked;
}

static void SetVehicleParamsEx(RPCParameters *parms)
{
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);

    unsigned short vehicleId;
    unsigned char engine;
    unsigned char lights;
    unsigned char alarm;
    unsigned char doors;
    unsigned char bonnet;
    unsigned char boot;
    unsigned char objective;

    bitStream.Read<unsigned short>(vehicleId);
    bitStream.Read<unsigned char>(engine);
    bitStream.Read<unsigned char>(lights);
    bitStream.Read<unsigned char>(alarm);
    bitStream.Read<unsigned char>(doors);
    bitStream.Read<unsigned char>(bonnet);
    bitStream.Read<unsigned char>(boot);
    bitStream.Read<unsigned char>(objective);

    if(vehicleId >= Zion::Client::vehicles.GetLength())
        return;

    CVehicle *vehicle = Zion::Client::vehicles[vehicleId];
    if(vehicle == nullptr)
        return;

    vehicle->m_nVehicleFlags.bEngineOn = engine;
    vehicle->m_nVehicleFlags.bLightsOn = lights;
    vehicle->m_nVehicleFlags.bSirenOrAlarm = alarm;
    vehicle->m_nDoorLock = doors;
}

static void GivePlayerMoney(RPCParameters *parms)
{
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);

    int ammount;
    bitStream.Read<int>(ammount);

    player->GetPlayerInfoForThisPlayerPed()->m_nMoney += ammount;
}

static void ResetPlayerMoney(RPCParameters *parms)
{
    player->GetPlayerInfoForThisPlayerPed()->m_nMoney = 0;
}

static void LinkVehicleToInterior(RPCParameters *parms)
{
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);

    unsigned short vehicleId;
    unsigned char interior;

    bitStream.Read<unsigned short>(vehicleId);
    bitStream.Read<unsigned char>(interior);

    if(vehicleId >= Zion::Client::vehicles.GetLength())
        return;

    CVehicle *vehicle = Zion::Client::vehicles[vehicleId];
    if(vehicle == nullptr)
        return;

    vehicle->m_nAreaCode = interior;
}

static void RemovePlayerFromVehicle(RPCParameters *parms)
{
    CVector position = player->GetPosition();
    position.x -= 1.4F;
    position.y += 0.3F;
    position.z += 0.3F;
    player->Teleport(position, false);
}

static void SetVehicleHealth(RPCParameters *parms)
{
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);

    unsigned short vehicleId;
    float health;

    bitStream.Read<unsigned short>(vehicleId);
    bitStream.Read<float>(health);

    if(vehicleId >= Zion::Client::vehicles.GetLength())
        return;

    CVehicle *vehicle = Zion::Client::vehicles[vehicleId];
    if(vehicle == nullptr)
        return;

    vehicle->m_fHealth = health;
}

static void SetVehiclePosition(RPCParameters *parms)
{
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);

    unsigned short vehicleId;
    Zion::Vector3F position;

    bitStream.Read<unsigned short>(vehicleId);
    bitStream.Read<Zion::Vector3F>(position);

    if(vehicleId >= Zion::Client::vehicles.GetLength())
        return;

    CVehicle *vehicle = Zion::Client::vehicles[vehicleId];
    if(vehicle == nullptr)
        return;

    vehicle->SetPosn(position.x, position.y, position.z);
}

static void SetVehicleVelocity(RPCParameters *parms)
{
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);

    unsigned short vehicleId;
    unsigned char turn;
    Zion::Vector3F velocity;

    bitStream.Read<unsigned short>(vehicleId);
    bitStream.Read<unsigned char>(turn);
    bitStream.Read<Zion::Vector3F>(velocity);

    if(vehicleId >= Zion::Client::vehicles.GetLength())
        return;

    CVehicle *vehicle = Zion::Client::vehicles[vehicleId];
    if(vehicle == nullptr)
        return;

    vehicle->m_vecMoveSpeed = velocity;
    vehicle->ApplyMoveSpeed();
}

static void SetVehiclerotation(RPCParameters *parms)
{
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);

    unsigned short vehicleId;
    float rotation;

    bitStream.Read<unsigned short>(vehicleId);
    bitStream.Read<float>(rotation);

    if(vehicleId >= Zion::Client::vehicles.GetLength())
        return;

    CVehicle *vehicle = Zion::Client::vehicles[vehicleId];
    if(vehicle == nullptr)
        return;

    vehicle->SetHeading(Zion::Util::DegressToRadians(rotation));
}

static void TogglePlayerSpectating(RPCParameters *parms)
{
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);

    unsigned char toggle;
    bitStream.Read<unsigned char>(toggle);

    if(toggle)
    {
        CVector position = player->GetPosition();
        position.x -= 1.4F;
        position.y += 0.3F;
        position.z += 0.3F;
        player->Teleport(position, false);

        TheCamera.SetPosn(50.0F, 50.0F, 50.0F);

        CVector lookAt(60.0F, 60.0F, 50.0F);
        TheCamera.TakeControlNoEntity(&lookAt, SWITCHTYPE_JUMPCUT, 1);

        Zion::LocalPlayer::spectating = true;
        Zion::LocalPlayer::spectatingType = Zion::LocalPlayer::SPECTATING_TYPE_NONE;
        Zion::LocalPlayer::spectatingMode = -1;
    }
    else
    {
        Zion::LocalPlayer::spectating = false;
        Zion::LocalPlayer::spectatingType = -1;
        Zion::LocalPlayer::spectatingMode = -1;
    }
}

static void GivePlayerWeapon(RPCParameters *parms) {
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);

    int model;
    int id;
    int ammo;

    bitStream.Read<int>(id);
    bitStream.Read<int>(ammo);

    switch(id) {
        case WEAPON_BRASSKNUCKLE:
            model = MODEL_BRASSKNUCKLE;
            break;

        case WEAPON_GOLFCLUB:
            model = MODEL_GOLFCLUB;
            break;

        case WEAPON_NIGHTSTICK:
            model = MODEL_NITESTICK;
            break;

        case WEAPON_KNIFE:
            model = MODEL_KNIFECUR;
            break;

        case WEAPON_BASEBALLBAT:
            model = MODEL_BAT;
            break;

        case WEAPON_SHOVEL:
            model = MODEL_SHOVEL;
            break;

        case WEAPON_POOLCUE:
            model = MODEL_POOLCUE;
            break;

        case WEAPON_KATANA:
            model = MODEL_KATANA;
            break;

        case WEAPON_CHAINSAW:
            model = MODEL_CHNSAW;
            break;

        case WEAPON_DILDO1:
            model = MODEL_GUN_DILDO1;
            break;

        case WEAPON_DILDO2:
            model = MODEL_GUN_DILDO2;
            break;

        case WEAPON_VIBE1:
            model = MODEL_GUN_VIBE1;
            break;

        case WEAPON_VIBE2:
            model = MODEL_GUN_VIBE2;
            break;

        case WEAPON_FLOWERS:
            model = MODEL_FLOWERA;
            break;

        case WEAPON_CANE:
            model = MODEL_GUN_CANE;
            break;

        case WEAPON_GRENADE:
            model = MODEL_GRENADE;
            break;

        case WEAPON_TEARGAS:
            model = MODEL_TEARGAS;
            break;

        case WEAPON_MOLOTOV:
            model = MODEL_MOLOTOV;
            break;

        case WEAPON_PISTOL:
            model = MODEL_COLT45;
            break;

        case WEAPON_PISTOL_SILENCED:
            model = MODEL_SILENCED;
            break;

        case WEAPON_DESERT_EAGLE:
            model = MODEL_DESERT_EAGLE;
            break;

        case WEAPON_SHOTGUN:
            model = MODEL_CHROMEGUN;
            break;

        case WEAPON_SAWNOFF:
            model = MODEL_SAWNOFF;
            break;

        case WEAPON_SPAS12:
            model = MODEL_SHOTGSPA;
            break;

        case WEAPON_MICRO_UZI:
            model = MODEL_MICRO_UZI;
            break;

        case WEAPON_MP5:
            model = MODEL_MP5LNG;
            break;

        case WEAPON_AK47:
            model = MODEL_AK47;
            break;

        case WEAPON_M4:
            model = MODEL_M4;
            break;

        case WEAPON_TEC9:
            model = MODEL_TEC9;
            break;

        case WEAPON_COUNTRYRIFLE:
            model = MODEL_CUNTGUN;
            break;

        case WEAPON_SNIPERRIFLE:
            model = MODEL_SNIPER;
            break;

        case WEAPON_RLAUNCHER:
            model = MODEL_ROCKETLA;
            break;

        case WEAPON_RLAUNCHER_HS:
            model = MODEL_HEATSEEK;
            break;

        case WEAPON_FTHROWER:
            model = MODEL_FLAME;
            break;

        case WEAPON_MINIGUN:
            model = MODEL_MINIGUN;
            break;

        case WEAPON_SATCHEL_CHARGE:
            model = MODEL_SATCHEL;
            break;

        case WEAPON_DETONATOR:
            model = MODEL_BOMB;
            break;

        case WEAPON_SPRAYCAN:
            model = MODEL_SPRAYCAN;
            break;

        case WEAPON_EXTINGUISHER:
            model = MODEL_FIRE_EX;
            break;

        case WEAPON_CAMERA:
            model = MODEL_CAMERA;
            break;

        case WEAPON_NIGHTVISION:
            model = MODEL_SANCHEZ;
            break;

        case WEAPON_INFRARED:
            model = MODEL_IRGOGGLES;
            break;

        case WEAPON_PARACHUTE:
            model = MODEL_PARACHUTE;
            break;

        case WEAPON_ARMOUR:
            model = MODEL_ARMOUR;
            break;

        case WEAPON_FLARE:
            model = MODEL_FLARE;
            break;
    }

    if(CStreaming::HasModelLoaded(model) == false) {
        CStreaming::RequestModel(model, 0);
        CStreaming::LoadAllRequestedModels(false);
    }

    player->GiveWeapon((eWeaponType)id, ammo, false);
}

static void SetPlayerArmedWeapon(RPCParameters *parms) {
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);

    int weapon;
    bitStream.Read<int>(weapon);

    player->SetCurrentWeapon((eWeaponType)weapon);
}

static void TogglePlayerControllable(RPCParameters *parms)
{
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);

    unsigned char controllable;
    bitStream.Read<unsigned char>(controllable);

    Zion::LocalPlayer::controllable = controllable;
}

static void ServerQuit(RPCParameters *parms)
{
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);

    unsigned short playerId;
    unsigned char reason;
    
    bitStream.Read<unsigned short>(playerId);
    bitStream.Read<unsigned char>(reason);

    if(playerId < Zion::Client::players.GetLength())
    {
        Zion::RemotePlayer *remotePlayer = Zion::Client::players[playerId];
        if(remotePlayer != nullptr)
        {
            delete remotePlayer;
            Zion::Client::players[playerId] = nullptr;

            if(playerId == Zion::Client::players.GetLength() - 1) {
                while(Zion::Client::players.GetLength() > 0 && Zion::Client::players.Back() == nullptr)
                    Zion::Client::players.Pop();
            }
        }
    }
}

static void ClientMessage(RPCParameters *parms)
{
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);

    unsigned int color;
    unsigned int length;

    bitStream.Read<unsigned int>(color);
    bitStream.Read<unsigned int>(length);

    char *message = new char[length + 1];
    bitStream.Read(message, length);
    message[length] = 0;

    Zion::ChatWindow::AddChat(nullptr, 0, message, color);
}

static void Chat(RPCParameters *parms)
{
    RakNet::BitStream bitStream(
        parms->input, (parms->numberOfBitsOfData / 8) + 1, false);

    unsigned short playerId;
    unsigned char length;
    char text[255];

    bitStream.Read<unsigned short>(playerId);
    bitStream.Read<unsigned char>(length);
    bitStream.Read(text, length);
    text[length] = 0;

    if(playerId < Zion::Client::players.GetLength()) {
        Zion::RemotePlayer *remotePlayer = Zion::Client::players[playerId];
        if(remotePlayer != nullptr)
            Zion::ChatWindow::AddChat(remotePlayer->nickname, remotePlayer->color, text, 0xFFFFFFFF);
    }
}

void Zion::RPCs::RegisterRPCs(RakClient *rakClient)
{
    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::TOGGLE_CLOCK, ToggleClock);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::TOGGLE_PLAYER_CONTROLLABLE, TogglePlayerControllable);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::CHAT, Chat);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::CLIENT_MESSAGE, ClientMessage);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::SERVER_QUIT, ServerQuit);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::SET_PLAYER_ARMED_WEAPON, SetPlayerArmedWeapon);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::GIVE_PLAYER_WEAPON, GivePlayerWeapon);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::TOGGLE_PLAYER_SPECTATING, TogglePlayerSpectating);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::SET_VEHICLE_Z_ANGLE, SetVehiclerotation);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::SET_VEHICLE_VELOCITY, SetVehicleVelocity);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::SET_VEHICLE_POS, SetVehiclePosition);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::SET_VEHICLE_HEALTH, SetVehicleHealth);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::REMOVE_PLAYER_FROM_VEHICLE, RemovePlayerFromVehicle);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::LINK_VEHICLE_TO_INTERIOR, LinkVehicleToInterior);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::RESET_PLAYER_MONEY, ResetPlayerMoney);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::GIVE_PLAYER_MONEY, GivePlayerMoney);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::SET_VEHICLE_PARAMS_EX, SetVehicleParamsEx);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::SET_VEHICLE_PARAMS_FOR_PLAYER, SetVehicleParamsForPlayer);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::SET_CAMERA_BEHIND_PLAYER, SetCameraBehindPlayer);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::SET_PLAYER_NAME, SetPlayerName);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::SET_SPAWN_INFO, SetSpawnInfo);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::SET_PLAYER_SKIN, SetPlayerSkin);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::SET_PLAYER_FIGHTING_STYLE, SetPlayerFightingStyle);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::FORCE_CLASS_SELECTION, ForceClassSelection);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::SET_GRAVITY, SetGravity);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::PUT_PLAYER_IN_VEHICLE, PutPlayerInVehicle);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::DISPLAY_GAME_TEXT, DisplayGameText);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::SET_PLAYER_DRUNK_LEVEL, SetPlayerDrunkLevel);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::SET_PLAYER_AMMO, SetPlayerAmmo);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::SET_PLAYER_ARMOUR, SetPlayerArmour);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::SET_PLAYER_HEALTH, SetPlayerHealth);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::SET_PLAYER_POS_FIND_Z, SetPlayerPositionFindZ);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::ENABLE_STUNT_BONUS_FOR_PLAYER, EnableStuntBonusForPlayer);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::CREATE_EXPLOSION, CreateExplosion);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::CLICK_TEXT_DRAW, ClickTextDraw);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::SHOW_DIALOG, ShowDialog);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::TEXT_DRAW_SET_STRING, TextDrawSetString);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::TEXT_DRAW_HIDE, TextDrawHide);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::SHOW_TEXT_DRAW, ShowTextDraw);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::SERVER_JOIN, ServerJoin);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::WORLD_PLAYER_ADD, WorldPlayerAdd);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::INIT_GAME, InitGame);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::REQUEST_SPAWN, RequestSpawn);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::REQUEST_CLASS, RequestClass);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::SET_PLAYER_POS, SetPlayerPosition);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::SET_PLAYER_FACING_ANGLE, SetPlayerFacingAngle);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::SET_PLAYER_CAMERA_POS, SetPlayerCameraPosition);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::SET_PLAYER_CAMERA_LOOK_AT, SetPlayerCameraLookAt);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::SET_PLAYER_INTERIOR, SetPlayerInterior);

    rakClient->RegisterAsRemoteProcedureCall(
        SAMP::RPC::WORLD_VEHICLE_ADD, WorldVehicleAdd);
}