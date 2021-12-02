#include "Zion/RemotePlayer.hh"
#include "Zion/Util.hh"
#include "Game/CStreaming.h"
#include "Game/CWorld.h"
#include "Game/CCarEnterExit.h"
#include <string.h>

static inline float Offset(float x, float y)
{
    if(x > y)
        return x - y;
    
    return y - x;
}

Zion::RemotePlayer *Zion::RemotePlayer::CreateRemotePlayer(const char *nickname, int id)
{
    return new RemotePlayer(nickname, id);
}

Zion::RemotePlayer::RemotePlayer(const char *nickname, int id)
{
    this->ped = new CPlayerPed(id + 2, false);
    this->ped->m_nPedType = PED_TYPE_PLAYER2;
    this->pad = new CPad;
    strcpy(this->nickname, nickname);
}

Zion::RemotePlayer::~RemotePlayer()
{
    delete this->ped;
    delete this->pad;
}

void Zion::RemotePlayer::Spawn(int skin, Vector3F position, float rotation)
{
    if(CStreaming::HasModelLoaded(skin) == false)
    {
        CStreaming::RequestModel(skin, 0);
        CStreaming::LoadAllRequestedModels(false);
    }

    this->ped->SetPosn(position.x, position.y, position.z);
    this->ped->SetModelIndex(skin);
    this->ped->m_fAimingRotation = Util::DegressToRadians(rotation);
    this->ped->m_fCurrentRotation = Util::DegressToRadians(rotation);

    CWorld::Add(this->ped);
}

void Zion::RemotePlayer::UpdateKeys(unsigned short lr, unsigned short ud, unsigned short keys)
{
    this->pad->NewState.LeftStickX = lr;
    this->pad->NewState.LeftStickY = ud;
    this->pad->NewState.RightStickX = 0;
    this->pad->NewState.RightStickY = 0;
    this->pad->NewState.LeftShoulder1 = 0;
    this->pad->NewState.LeftShoulder2 = 0;
    this->pad->NewState.RightShoulder1 = 0;
    this->pad->NewState.RightShoulder2 = 0;
    this->pad->NewState.DPadUp = 0;
    this->pad->NewState.DPadDown = 0;
    this->pad->NewState.DPadLeft = 0;
    this->pad->NewState.DPadRight = 0;
    this->pad->NewState.Start = 0;
    this->pad->NewState.Select = 0;
    this->pad->NewState.ButtonSquare = 0;
    this->pad->NewState.ButtonTriangle = 0;
    this->pad->NewState.ButtonCross = 0;
    this->pad->NewState.ButtonCircle = 0;
    this->pad->NewState.ShockButtonL = 0;
    this->pad->NewState.ShockButtonR = 0;
    this->pad->NewState.m_bChatIndicated = 0;
    this->pad->NewState.m_bPedWalk = 0;
    this->pad->NewState.m_bVehicleMouseLook = 0;
    this->pad->NewState.m_bRadioTrackSkip = 0;

    // Action
    if(keys & 1)
        this->pad->NewState.LeftShoulder1 = 255;

    keys >>= 1;

    // Crouch
    if(keys & 1)
        this->pad->NewState.ShockButtonL = 255;
    
    keys >>= 1;

    // Fire
    if(keys & 1)
        this->pad->NewState.ButtonCircle = 255;
    
    keys >>= 1;

    // Sprint
    if(keys & 1)
        this->pad->NewState.ButtonCross = 255;
    
    keys >>= 1;

    // Secondary attack
    if(keys & 1)
        this->pad->NewState.LeftShoulder1 = 255;
    
    keys >>= 1;

    // Jump
    if(keys & 1)
        this->pad->NewState.ButtonSquare = 255;
    
    keys >>= 1;

    // Look right
    if(keys & 1)
        this->pad->NewState.RightStickX = 128;
    
    keys >>= 1;

    // Handbrake
    if(keys & 1)
        this->pad->NewState.RightShoulder1 = 255;
    
    keys >>= 1;

    // Look left
    if(keys & 1)
        this->pad->NewState.RightStickX = -128;
    
    keys >>= 1;

    // Submission
    if(keys & 1)
        this->pad->NewState.ShockButtonR = 255;
    
    keys >>= 1;

    // Walk
    if(keys & 1)
        this->pad->NewState.m_bPedWalk = 1;
    
    keys >>= 1;

    // Submission
    if(keys & 1)
        this->pad->NewState.ShockButtonR = 255;
    
    keys >>= 1;

    // Walk
    if(keys & 1)
        this->pad->NewState.m_bPedWalk = 1;
}

void Zion::RemotePlayer::UpdateOnFootData(Player::OnFootData onFootData)
{
    if(this->ped->m_nPedFlags.bInVehicle)
    {
        CVector position = this->ped->GetPosition();
        position.x -= 1.4F;
        position.y += 0.3F;
        position.z += 0.3F;
        this->ped->Teleport(position, false);
    }

    this->ped->m_fHealth = onFootData.health;
    this->ped->m_fArmour = onFootData.armour;
    this->ped->m_vecMoveSpeed.x = onFootData.moveSpeed.x;
    this->ped->m_vecMoveSpeed.y = onFootData.moveSpeed.y;
    this->ped->m_vecMoveSpeed.z = onFootData.moveSpeed.z;
    this->ped->ApplyMoveSpeed();

    this->UpdateKeys(onFootData.lrAnalog, onFootData.udAnalog, onFootData.keys);
    this->Ped_UpdateRotation(onFootData.quaternion);
    this->Ped_UpdateTargetPosition(onFootData.position);

    eWeaponType weapon = (eWeaponType)(onFootData.currentWeapon & 0x3F);
    this->ped->SetCurrentWeapon(weapon);

    if(this->ped->m_aWeapons[this->ped->m_nActiveWeaponSlot].m_nType != weapon)
    {
        this->ped->GiveWeapon(weapon, 9999, false);
        this->ped->SetCurrentWeapon(weapon);
    }
}

void Zion::RemotePlayer::UpdateInCarData(Player::InCarData inCarData)
{
    if(this->ped->m_nPedFlags.bInVehicle == false)
        CCarEnterExit::SetPedInCarDirect(this->ped, this->vehicle, 0, true);

    this->ped->m_fHealth = inCarData.playerHealth;
    this->ped->m_fArmour = inCarData.playerArmour;
    this->vehicle->m_fHealth = inCarData.carHealth;
    this->vehicle->m_vecMoveSpeed = inCarData.moveSpeed;
    this->vehicle->ApplyMoveSpeed();

    this->UpdateKeys(inCarData.lrAnalog, inCarData.udAnalog, inCarData.keys);
    this->Vehicle_UpdateRotation(inCarData.quaternion);
    this->Vehicle_UpdateTargetPosition(inCarData.position);

    eWeaponType weapon = (eWeaponType)(inCarData.currentWeapon & 0x3F);
    this->ped->SetCurrentWeapon(weapon);

    if(this->ped->m_aWeapons[this->ped->m_nActiveWeaponSlot].m_nType != weapon)
    {
        this->ped->GiveWeapon(weapon, 9999, false);
        this->ped->SetCurrentWeapon(weapon);
    }
}

void Zion::RemotePlayer::Ped_UpdateRotation(Vector4F quaternion)
{
    Vector4F pquaternion; 
    pquaternion = *this->ped->m_matrix;
    
    quaternion.Slerp(pquaternion, 0.75F);
    
    this->ped->SetMatrix(quaternion);
}

void Zion::RemotePlayer::Ped_UpdateTargetPosition(Vector3F targetPosition)
{
    CVector position = this->ped->GetPosition();

    if(position.x != targetPosition.x || position.y != targetPosition.y || position.z != targetPosition.z)
    {
        CVector vector;
        vector.x = Offset(targetPosition.x, position.x);
        vector.y = Offset(targetPosition.y, position.y);
        vector.z = Offset(targetPosition.z, position.z);

        if(vector.x > 2.0F || vector.y > 2.0F || vector.z > 1.0F)
            this->ped->SetPosn(targetPosition);
        else
        {
            this->ped->m_vecMoveSpeed.x += (targetPosition.x - position.x) * 0.1F;
            this->ped->m_vecMoveSpeed.y += (targetPosition.y - position.y) * 0.1F;
            this->ped->m_vecMoveSpeed.z += (targetPosition.z - position.z) * 0.1F;
            this->ped->ApplyMoveSpeed();
        }
    }
}

void Zion::RemotePlayer::Vehicle_UpdateRotation(Vector4F quaternion)
{
    Vector4F vquaternion;
    vquaternion = *this->vehicle->m_matrix;

    quaternion.Slerp(vquaternion, 0.75F);
    quaternion.Normalize();

    this->vehicle->SetMatrix(quaternion);
}

void Zion::RemotePlayer::Vehicle_UpdateTargetPosition(Vector3F targetPosition)
{
    CVector position = this->vehicle->GetPosition();

    if(position.x != targetPosition.x || position.y != targetPosition.y || position.z != targetPosition.z)
    {
        CVector vector;
        vector.x = Offset(targetPosition.x, position.x);
        vector.y = Offset(targetPosition.y, position.y);
        vector.z = Offset(targetPosition.z, position.z);

        if(vector.x > 2.0F || vector.y > 2.0F || vector.z > 1.0F)
            this->vehicle->SetPosn(targetPosition);
        else
        {
            this->vehicle->m_vecMoveSpeed.x += (targetPosition.x - position.x) * 0.1F;
            this->vehicle->m_vecMoveSpeed.y += (targetPosition.y - position.y) * 0.1F;
            this->vehicle->m_vecMoveSpeed.z += (targetPosition.z - position.z) * 0.1F;
            this->vehicle->ApplyMoveSpeed();
        }
    }
}