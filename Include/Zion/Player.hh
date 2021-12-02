#pragma once
#include "Vector.hh"

namespace Zion
{
    class Player
    {
        public:
            class SpecialAction
            {
                public:
                    enum
                    {
                        None,
                        Duck,
                        UseJetPack,
                        EnterVehicle,
                        ExitVehicle,
                        Dance1,
                        Dance2,
                        Dance3,
                        Dance4,
                        Handsup = 10,
                        UseCellphone,
                        Sitting,
                        StopUseCellphone,
                        DrinkBeer = 20,
                        SmokeCiggy,
                        DrinkWine,
                        DrinkSprunk,
                        Cuffed,
                        Carry,
                    };
            };

            struct OnFootData
            {
                unsigned short  lrAnalog;
                unsigned short  udAnalog;
                unsigned short  keys;
                Vector3F        position;
                Vector4F        quaternion;
                unsigned char   health;
                unsigned char   armour;
                unsigned char   currentWeapon;
                unsigned char   specialAction;
                Vector3F        moveSpeed;
                Vector3F        surfOffsets;
                unsigned short  surfInfo;
                int             animation;
            } __attribute__((packed));

            struct InCarData
            {
                unsigned short  vehicleId;
                unsigned short  lrAnalog;
                unsigned short  udAnalog;
                unsigned short  keys;
                Vector4F        quaternion;
                Vector3F        position;
                Vector3F        moveSpeed;
                float           carHealth;
                unsigned char   playerHealth;
                unsigned char   playerArmour;
                unsigned char   currentWeapon;
                unsigned char   sirenOn;
                unsigned char   landingGearState;
                unsigned short  trailerIdOrThrustAngle;
                float           trainSpeed;
            } __attribute__((packed));

            struct SpawnData
            {
                unsigned char   team;
                int             skin;
                unsigned char   unknown;
                Vector3F        position;
                float           rotation;
                int             spawnWeapons[3];
                int             spawnWeaponsAmmo[3];
            } __attribute__((packed));

            struct AimData
            {
                unsigned char   camMode;
                Vector3F        aimf1;
                Vector3F        aimPosition;
                float           aimZ;
                unsigned char   camExtZoom : 6;
                unsigned char   weaponState : 2;
                unsigned char   aspectRatio;
            } __attribute__((packed));

            struct BulletData
            {
                unsigned char   hitType;
                unsigned short  hitId;
                Vector3F        hitOrigin;
                Vector3F        hitTarget;
                Vector3F        centerOfHit;
                unsigned char   weaponId;
            } __attribute__((packed));

            struct PassengerData
            {
                unsigned short  vehicleId;
                unsigned char   seatFlags : 7;
                unsigned char   driveBy : 1;
                unsigned char   currentWeapon;
                unsigned char   playerHealth;
                unsigned char   playerArmour;
                unsigned short  lrAnalog;
                unsigned short  udAnalog;
                unsigned short  keys;
                Vector3F        position;
            } __attribute__((packed));

            struct SpectatorData
            {
                unsigned short lrAnalog;
                unsigned short udAnalog;
                unsigned short keys;
                Vector3F position;
            } __attribute__((packed));
    };
};