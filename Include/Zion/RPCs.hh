#pragma once
#include "RakNet/RakClient.h"

namespace Zion
{
    class RPCs
    {
        public:
            static void RegisterRPCs(RakClient *rakClient);
    };
}