#include "Zion/Client.hh"
#include "Zion/Log.hh"
#include "Zion/RPCs.hh"
#include "Zion/Main.hh"
#include "RakNet/RakClient.h"
#include "RakNet/SAMP/SAMP.h"
#include "RakNet/PacketEnumerations.h"
#include <stdlib.h>

static RakClient *rakClient = nullptr;

static inline bool Send(
    RakNet::BitStream *bitStream, PacketPriority priority, PacketReliability reliability)
{
    return rakClient->Send(bitStream, priority, reliability, 0);
}

static inline bool RPC(
    unsigned char uniqueId, RakNet::BitStream *bitStream, PacketPriority priority,
    PacketReliability reliability)
{
    return rakClient->RPC(uniqueId, bitStream, priority, reliability, 0, false, UNASSIGNED_NETWORK_ID, nullptr);
}

static void AuthKey(unsigned char *data, unsigned long size)
{
    RakNet::BitStream bitStream(data, size, false);

    unsigned char authLength;
    char auth[256];
    bitStream.Read<unsigned char>(authLength);
    bitStream.Read(auth, authLength);
    auth[authLength] = '\0';

    // ================================================================

    char authKey[260];
    unsigned char authKeyLength;

    SAMP::GenerateAuthKey(authKey, auth);
    authKeyLength = strlen(authKey);

    bitStream = RakNet::BitStream();
    bitStream.Write<unsigned char>(ID_AUTH_KEY);
    bitStream.Write<unsigned char>(authKeyLength);
    bitStream.Write(authKey, authKeyLength);
    Send(&bitStream, SYSTEM_PRIORITY, RELIABLE);
}

static void ConnectionSucceeded()
{
    int nicknameLength = strlen(Zion::Client::nickname);
    if(nicknameLength >= 24)
    {
        Zion::Log::Write("[ERROR] nickname too long\n");
        exit(1);
    }

    RakNet::BitStream bitStream;
    bitStream.Write<int>(4057);
    bitStream.Write<unsigned char>(1);
    bitStream.Write<unsigned char>(nicknameLength);
    bitStream.Write(Zion::Client::nickname, nicknameLength);
    bitStream.Write<unsigned int>(SAMP::token ^ 4057);
    bitStream.Write<unsigned char>(44);
    bitStream.Write("15121F6F18550C00AC4B4F8A167D0379BB0ACA99043", 44);
    bitStream.Write<unsigned char>(6);
    bitStream.Write("0.3.7", 6);
    RPC(SAMP::RPC::CLIENT_JOIN, &bitStream, HIGH_PRIORITY, RELIABLE);

    Zion::Main::player = CPlayerPed::GetPlayerPed(-1);
    Zion::Main::pad = CPad::GetPad(0);
}

static void PlayerSync(unsigned char *data, unsigned long size)
{
    RakNet::BitStream bitStream(data, size, false);
    unsigned short playerId;
    unsigned short lrAnalog = 0;
    unsigned short udAnalog = 0;
    unsigned short keys = 0;
    Zion::Vector3F position;
    Zion::Vector4F quaternion;
    unsigned char health = 0;
    unsigned char armour = 0;
    unsigned char currentWeapon = 0;
    unsigned char specialAction = 0;
    Zion::Vector3F moveSpeed;
    Zion::Vector3F surfOffsets;
    unsigned short surfInfo = 0xFFFF;
    int animation = 0;
    bool aux = false;
    Zion::RemotePlayer *player = nullptr;

    bitStream.Read<unsigned short>(playerId);
    if(playerId >= Zion::Client::players.GetLength())
        return;

    player = Zion::Client::players[playerId];
    if(player == nullptr)
        return;

    bitStream.Read<bool>(aux);
    if(aux)
        bitStream.Read<unsigned short>(lrAnalog);                        

    bitStream.Read<bool>(aux);
    if(aux)
        bitStream.Read<unsigned short>(udAnalog);

    bitStream.Read<unsigned short>(keys);
    bitStream.Read<Zion::Vector3F>(position);
    bitStream.ReadNormQuat(quaternion.w, quaternion.x, quaternion.y, quaternion.z);

    unsigned char healthArmour;
    bitStream.Read<unsigned char>(healthArmour);

    health = healthArmour >> 4;
    armour = healthArmour & 0x0F;

    if(health == 0xF) 
        health = 100;
    else
        health *= 7;       

    if(armour == 0xF) 
        armour = 100;
    else
        armour *= 7;  

    bitStream.Read<unsigned char>(currentWeapon);               
    bitStream.Read<unsigned char>(specialAction);    
    bitStream.ReadVector(moveSpeed.x, moveSpeed.y, moveSpeed.z); 

    bitStream.Read<bool>(aux);
    if(aux)
    {
        bitStream.Read<unsigned short>(surfInfo);
        bitStream.Read<Zion::Vector3F>(surfOffsets);
    } 

    Zion::Player::OnFootData onFootData;
    onFootData.lrAnalog = lrAnalog;
    onFootData.udAnalog = udAnalog;
    onFootData.keys = keys;
    onFootData.position = position;
    onFootData.quaternion = quaternion;
    onFootData.health = health;
    onFootData.armour = armour;
    onFootData.currentWeapon = currentWeapon;
    onFootData.specialAction = specialAction;
    onFootData.moveSpeed = moveSpeed;
    onFootData.surfOffsets = surfOffsets;
    onFootData.surfInfo = surfInfo;
    onFootData.animation = animation;
    player->UpdateOnFootData(onFootData);
}

static void VehicleSync(unsigned char *data, unsigned long size)
{
    RakNet::BitStream bitStream(data, size, false);

    unsigned short      vehicleId = 0xFFFF;
    unsigned short      lrAnalog = 0;
    unsigned short      udAnalog = 0;
    unsigned short      keys = 0;
    Zion::Vector4F      quaternion = {0.0F, 0.0F, 0.0F, 0.0F};
    Zion::Vector3F      position = {0.0F, 0.0F, 0.0F};
    Zion::Vector3F      moveSpeed = {0.0F, 0.0F, 0.0F};
    unsigned short      carHealth = 0;
    unsigned char       playerHealth = 0;
    unsigned char       playerArmour = 0;
    unsigned char       currentWeapon = 0;
    unsigned char       sirenOn = 0;
    unsigned char       landingGearState = 0;
    unsigned short      trailerIdOrThrustAngle = 0;
    float               trainSpeed = 0.0F;
    bool                aux = false;
    unsigned short      playerId = 0xFFFF;
    unsigned char       playerHealthArmour = 0;
    Zion::RemotePlayer  *player = nullptr;
    CVehicle            *vehicle = nullptr;

    bitStream.Read<unsigned short>(playerId);

    if(playerId < Zion::Client::players.GetLength())
    {
        player = Zion::Client::players[playerId];
        if(player == nullptr)
            return;
    }
    else
        return;

    bitStream.Read<unsigned short>(vehicleId);

    if(vehicleId < Zion::Client::vehicles.GetLength())
    {
        vehicle = Zion::Client::vehicles[vehicleId];
        if(vehicle == nullptr)
            return;
    }
    else
        return;

    bitStream.Read<unsigned short>(lrAnalog);
    bitStream.Read<unsigned short>(udAnalog);
    bitStream.Read<unsigned short>(keys);
    bitStream.ReadNormQuat(quaternion.w, quaternion.x, quaternion.y, quaternion.z);
    bitStream.Read<Zion::Vector3F>(position);
    bitStream.ReadVector(moveSpeed.x, moveSpeed.y, moveSpeed.z);
    bitStream.Read<unsigned short>(carHealth);
    bitStream.Read<unsigned char>(playerHealthArmour);
    
    if((playerHealthArmour & 0x0F) == 0xF)
        playerArmour = 100;
    else
        playerArmour = (playerHealthArmour & 0x0F) * 7;

    if((playerHealthArmour >> 4) == 0xF)
        playerHealth = 100;
    else
        playerHealth = (playerHealthArmour >> 4) * 7;

    bitStream.Read<unsigned char>(currentWeapon);

    bitStream.Read<bool>(aux);
    sirenOn = aux;

    bitStream.Read<bool>(aux);
    landingGearState = aux;

    bitStream.Read<bool>(aux);
    if(aux)
        bitStream.Read<unsigned short>(trailerIdOrThrustAngle);

    Zion::Player::InCarData inCarData;
    inCarData.vehicleId = vehicleId;
    inCarData.lrAnalog = lrAnalog;
    inCarData.udAnalog = udAnalog;
    inCarData.keys = keys;
    inCarData.quaternion = quaternion;
    inCarData.position = position;
    inCarData.moveSpeed = moveSpeed;
    inCarData.carHealth = carHealth;
    inCarData.playerHealth = playerHealth;
    inCarData.playerArmour = playerArmour;
    inCarData.currentWeapon = currentWeapon;
    inCarData.sirenOn = sirenOn;
    inCarData.landingGearState = landingGearState;
    inCarData.trailerIdOrThrustAngle = trailerIdOrThrustAngle;
    inCarData.trainSpeed = trainSpeed;
    player->vehicle = vehicle;
    player->UpdateInCarData(inCarData);
}

void Zion::Client::Connect()
{
    if(rakClient != nullptr)
        Disconnect();

    rakClient = new RakClient;
    rakClient->Connect(hostname, port, 0, 0, 6);
    RPCs::RegisterRPCs(rakClient);
    state = State::Connecting;
}

void Zion::Client::Disconnect()
{
    if(rakClient != nullptr)
    {
        rakClient->Disconnect(30);
        delete rakClient;
        rakClient = nullptr;
        state = State::Disconnected;
    }
}

void Zion::Client::Process()
{
    if(rakClient == nullptr)
        return;

    Packet *packet = rakClient->Receive();

    while(packet != nullptr)
    {
        switch(packet->data[0])
        {
            case ID_AUTH_KEY:
                AuthKey(packet->data + 1, (packet->bitSize / 8) + 1);
                break;

            case ID_CONNECTION_REQUEST_ACCEPTED:
                ConnectionSucceeded();
                break;

            case ID_CONNECTION_LOST:
            case ID_DISCONNECTION_NOTIFICATION:
                Disconnect();
                return;
                break;

            case SAMP::Packet::PLAYER_SYNC:
                PlayerSync(packet->data + 1, (packet->bitSize / 8) + 1);
                break;

            case SAMP::Packet::VEHICLE_SYNC:
                VehicleSync(packet->data + 1, (packet->bitSize / 8) + 1);
                break;
        }

        rakClient->DeallocatePacket(packet);
        packet = rakClient->Receive();
    }
}

void Zion::Client::SendOnFootData(Player::OnFootData onFootData)
{
    RakNet::BitStream bitStream;
    bitStream.Write<unsigned char>(SAMP::Packet::PLAYER_SYNC);
    bitStream.Write<Player::OnFootData>(onFootData);
    Send(&bitStream, HIGH_PRIORITY, UNRELIABLE_SEQUENCED);
}

void Zion::Client::RequestClass(int klass)
{
    RakNet::BitStream bitStream;
    bitStream.Write<int>(klass);
    RPC(SAMP::RPC::REQUEST_CLASS, &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED);
}

void Zion::Client::RequestSpawn()
{
    RPC(SAMP::RPC::REQUEST_SPAWN, nullptr, HIGH_PRIORITY, RELIABLE_ORDERED);
}

void Zion::Client::SendSpawn()
{
    RPC(SAMP::RPC::SPAWN, nullptr, HIGH_PRIORITY, RELIABLE_ORDERED);
}

void Zion::Client::SendTextDrawClick(unsigned short textDrawId)
{
    RakNet::BitStream bitStream;
    bitStream.Write<unsigned short>(textDrawId);
    RPC(SAMP::RPC::CLICK_TEXT_DRAW, &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED);
}

void Zion::Client::SendDialogResponse(unsigned short dialogId, unsigned char buttonId, unsigned short listItem, const char *input)
{
    int length = strlen(input);
    if(length >= 254)
        return;

    RakNet::BitStream bitStream;
    bitStream.Write<unsigned short>(dialogId);
    bitStream.Write<unsigned char>(buttonId);
    bitStream.Write<unsigned short>(listItem);
    bitStream.Write<unsigned char>(length);
    bitStream.Write(input, length);
    RPC(SAMP::RPC::DIALOG_RESPONSE, &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED);
}

void Zion::Client::SendCommand(const char *command)
{
    int commandLength = strlen(command);

    RakNet::BitStream bitStream;
    bitStream.Write<int>(commandLength);
    bitStream.Write(command, commandLength);
    RPC(SAMP::RPC::SERVER_COMMAND, &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED);
}

void Zion::Client::SendMessage(const char *message)
{
    int messageLength = strlen(message);
    if(messageLength >= 254)
        return;

    RakNet::BitStream bitStream;
    bitStream.Write<unsigned char>(messageLength);
    bitStream.Write(message, messageLength);
    RPC(SAMP::RPC::CHAT, &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED);
}

void Zion::Client::SendInCarData(Player::InCarData inCarData)
{
    RakNet::BitStream bitStream;
    bitStream.Write<unsigned char>(SAMP::Packet::VEHICLE_SYNC);
    bitStream.Write<Player::InCarData>(inCarData);
    Send(&bitStream, HIGH_PRIORITY, UNRELIABLE_SEQUENCED);
}

void Zion::Client::SendSpectatorData(Player::SpectatorData spectatorData)
{
    RakNet::BitStream bitStream;
    bitStream.Write<unsigned char>(SAMP::Packet::SPECTATOR_SYNC);
    bitStream.Write<Player::SpectatorData>(spectatorData);
    Send(&bitStream, HIGH_PRIORITY, UNRELIABLE_SEQUENCED);
}

const char *Zion::Client::nickname = nullptr;
const char *Zion::Client::hostname = nullptr;
unsigned short Zion::Client::port = 0;
unsigned short Zion::Client::id = 0;
int Zion::Client::classesAvalible = 0;
int Zion::Client::onFootSendRate = 0;
int Zion::Client::inCarSendRate = 0;
int Zion::Client::state = Zion::Client::State::Disconnected;
Zion::List<Zion::RemotePlayer *> Zion::Client::players;
Zion::List<CVehicle *> Zion::Client::vehicles;