#include "Zion/LocalPlayer.hh"
#include "Zion/Player.hh"
#include "Zion/Main.hh"
#include "Zion/Client.hh"
#include "Game/CTimer.h"
#include "Game/CCamera.h"

#define player Zion::Main::player
#define pad Zion::Main::pad

static int klass = 0;

static inline int GetVehicleId(CVehicle *vehicle)
{
    for(unsigned long index = 0; index < Zion::Client::vehicles.GetLength(); index++)
    {
        if(Zion::Client::vehicles[index] == vehicle)
            return index;
    }

    return 0xFFFF;
}

static inline unsigned short GetKeys()
{
    unsigned short keys = 0;
    
    // Analog right
    if(pad->NewState.LeftStickX > 0);
        keys |= 1;
    
    keys <<= 1;
    
    // Analog left
    if(pad->NewState.LeftStickX < 0)
        keys |= 1;
    
    keys <<= 1;
    
    // Analog down
    if(pad->NewState.LeftStickY > 0)
        keys |= 1;
    
    keys <<= 1;
    
    // Analog up
    if(pad->NewState.LeftStickY < 0)
        keys |= 1;
    
    keys <<= 1;
    
    // Walk
    if(pad->NewState.m_bPedWalk)
        keys |= 1;
    
    keys <<= 1;
    
    // Submission
    if(pad->NewState.ShockButtonR)
        keys |= 1;
    
    keys <<= 1;
    
    // Walk
    if(pad->NewState.m_bPedWalk)
        keys |= 1;
    
    keys <<= 1;
    
    // Submission
    if(pad->NewState.ShockButtonR)
        keys |= 1;
    
    keys <<= 1;
    
    // Look left
    if(pad->NewState.RightStickX < 0)
        keys |= 1;
    
    keys <<= 1;
    
    // Hadbrake
    if(pad->NewState.RightShoulder1)
        keys |= 1;
    
    keys <<= 1;
    
    // Look right
    if(pad->NewState.RightStickX > 0)
        keys |= 1;
    
    keys <<= 1;
    
    // Jump
    if(pad->NewState.ButtonSquare)
        keys |= 1;
    
    keys <<= 1;
    
    // Secondary attack
    if(pad->NewState.LeftShoulder1)
        keys |= 1;
    
    keys <<= 1;
    
    // Sprint
    if(pad->NewState.ButtonCross)
        keys |= 1;
    
    keys <<= 1;
    
    // Fire
    if(pad->NewState.ButtonCircle)
        keys |= 1;
    
    keys <<= 1;
    
    // Crouch
    if(pad->NewState.ShockButtonL)
        keys |= 1;
    
    keys <<= 1;
    
    // Action
    if(pad->NewState.LeftShoulder1)
        keys |= 1;

    return keys;
}

static void SendOnFootData()
{
    Zion::Player::OnFootData onFootData;

    onFootData.lrAnalog = pad->NewState.LeftStickX;
    onFootData.udAnalog = pad->NewState.LeftStickY;
    onFootData.keys = GetKeys();
    onFootData.position = player->GetPosition();
    onFootData.quaternion = *player->m_matrix;
    onFootData.quaternion.Normalize();
    onFootData.health = player->m_fHealth;
    onFootData.armour = player->m_fArmour;
    onFootData.currentWeapon = player->m_aWeapons[player->m_nActiveWeaponSlot].m_nType & 0x3F;
    onFootData.specialAction = player->m_nPedFlags.bIsDucking ?
        Zion::Player::SpecialAction::Duck : Zion::Player::SpecialAction::None;
    onFootData.moveSpeed = player->m_vecMoveSpeed;
    onFootData.surfOffsets.x = 0.0F;
    onFootData.surfOffsets.y = 0.0F;
    onFootData.surfOffsets.z = 0.0F;
    onFootData.surfInfo = 0.0F;
    onFootData.animation = player->m_nAnimGroup;

    Zion::Client::SendOnFootData(onFootData);
}

static void SendInCarData()
{
    Zion::Player::InCarData inCarData;
    memset(&inCarData, 0, sizeof(Zion::Player::InCarData));

    inCarData.vehicleId = GetVehicleId(player->m_pVehicle);
    inCarData.lrAnalog = pad->NewState.LeftStickX;
    inCarData.udAnalog = pad->NewState.LeftStickY;
    inCarData.keys = GetKeys();
    inCarData.position = player->m_pVehicle->GetPosition();
    inCarData.quaternion = *player->m_pVehicle->m_matrix;
    inCarData.quaternion.Normalize();
    inCarData.playerHealth = player->m_fHealth;
    inCarData.playerArmour = player->m_fArmour;
    inCarData.carHealth = player->m_pVehicle->m_fHealth;
    inCarData.currentWeapon = player->m_aWeapons[player->m_nActiveWeaponSlot].m_nType & 0x3F;
    inCarData.moveSpeed = player->m_pVehicle->m_vecMoveSpeed;

    Zion::Client::SendInCarData(inCarData);
}

static void SendSpectatorData()
{
    Zion::Player::SpectatorData spectatorData;
    spectatorData.lrAnalog = pad->NewState.LeftStickX;
    spectatorData.udAnalog = pad->NewState.LeftStickY;
    spectatorData.keys = GetKeys();
    spectatorData.position = player->GetPosition();

    Zion::Client::SendSpectatorData(spectatorData);
}

void Zion::LocalPlayer::NextClass()
{
    klass++;

    if(klass >= Client::classesAvalible)
        klass = 0;
    
    Client::RequestClass(klass);
}

void Zion::LocalPlayer::PreviousClass()
{
    klass--;

    if(klass < 0)
        klass = Client::classesAvalible - 1;
    
    Client::RequestClass(klass);
}

void Zion::LocalPlayer::Process()
{
    static unsigned int lastUpdate = 0;

    if(controllable == false)
        pad->DisablePlayerControls = true;

    if(spectating)
    {
        if(CTimer::m_snTimeInMilliseconds - lastUpdate >= 200)
        {
            SendSpectatorData();
            lastUpdate = CTimer::m_snTimeInMilliseconds;
        }
    }
    else
    {
        if(player->m_nPedFlags.bInVehicle)
        {
            if(CTimer::m_snTimeInMilliseconds - lastUpdate >= Client::inCarSendRate)
            {
                SendInCarData();
                lastUpdate = CTimer::m_snTimeInMilliseconds;
            }
        }
        else
        {
            if(CTimer::m_snTimeInMilliseconds - lastUpdate >= Client::onFootSendRate)
            {
                SendOnFootData();
                lastUpdate = CTimer::m_snTimeInMilliseconds;
            }
        }
    }
}

bool Zion::LocalPlayer::controllable = true;
bool Zion::LocalPlayer::spectating = false;
int Zion::LocalPlayer::spectatingMode = -1;
int Zion::LocalPlayer::spectatingType = -1;