#pragma once

namespace Zion
{
    class LocalPlayer
    {
        public:
            enum { 
                SPECTATING_MODE_VEHICLE = 3, 
                SPECTATING_MODE_PLAYER = 4, 
                SPECTATING_MODE_FIXED = 15,
                SPECTATING_MODE_SIDE = 14
            }; 

            enum { 
                SPECTATING_TYPE_NONE, 
                SPECTATING_TYPE_PLAYER, 
                SPECTATING_TYPE_VEHICLE
            }; 

            static void NextClass();
            static void PreviousClass();
            static void Process();

            static bool controllable;
            static bool spectating;
            static int spectatingMode;
            static int spectatingType;
    };
};