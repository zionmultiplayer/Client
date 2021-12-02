#pragma once
#include "Player.hh"
#include "List.hh"
#include "RemotePlayer.hh"
#include "Game/CVehicle.h"

namespace Zion
{
    class Client
    {
        public:
            class State
            {
                public:
                    enum
                    {
                        Disconnected,
                        Connected,
                        Connecting
                    };
            };

            static void Connect();
            static void Disconnect();
            static void Process();
            static void SendOnFootData(Player::OnFootData onFootData);
            static void RequestClass(int klass);
            static void RequestSpawn();
            static void SendSpawn();
            static void SendTextDrawClick(unsigned short textDrawId);
            static void SendDialogResponse(unsigned short dialogId, unsigned char buttonId, unsigned short listItem, const char *input);
            static void SendCommand(const char *command);
            static void SendMessage(const char *message);
            static void SendInCarData(Player::InCarData inCarData);
            static void SendSpectatorData(Player::SpectatorData spectatorData);

            static const char *nickname;
            static const char *hostname;
            static unsigned short port;
            static unsigned short id;
            static int classesAvalible;
            static int onFootSendRate;
            static int inCarSendRate;
            static int state;
            static List<RemotePlayer *> players;
            static List<CVehicle *> vehicles;
    };
};