#pragma once
#include "Game/CPlayerPed.h"
#include "Game/CPad.h"
#include "Vector.hh"
#include "Player.hh"

namespace Zion
{
    class RemotePlayer
    {
        public:
            static RemotePlayer *CreateRemotePlayer(const char *nickname, int id);

            ~RemotePlayer();

            void Spawn(int skin, Vector3F position, float rotation);
            void UpdateOnFootData(Player::OnFootData onFootData);
            void UpdateInCarData(Player::InCarData inCarData);

            CPlayerPed *ped;
            CVehicle *vehicle;
            CPad *pad;
            char nickname[32];
            unsigned int color;

        private:
            RemotePlayer(const char *nickname, int id);

            void UpdateKeys(unsigned short lr, unsigned short ud, unsigned short keys);
            void Ped_UpdateRotation(Vector4F quaternion);
            void Ped_UpdateTargetPosition(Vector3F targetPosition);
            void Vehicle_UpdateRotation(Vector4F quaternion);
            void Vehicle_UpdateTargetPosition(Vector3F targetPosition);
    };
}