#pragma once
#include <cstdint>
#include <cstddef>
#include <exception>

#define SAMP_CLIENT 1
#define SAMP_SERVER 0
#define NETCODE_CONNCOOKIELULZ 0x6969

#if defined(_WIN32) || defined(WIN32)
    #include <winsock2.h>
    #include <ws2tcpip.h>
#else
    #include <netinet/in.h>
    typedef int SOCKET;
    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
#endif

#if __has_include(<MTUSize.h>) 
    #include <MTUSize.h> 
#endif

#ifndef MAXIMUM_MTU_SIZE
    #define MAXIMUM_MTU_SIZE 1500
#endif

#define MAX_AUTH_RESPONSE_LEN   (64)
#define MAX_UNVERIFIED_RPCS     (5)

namespace SAMP {
    class ChecksumException : public std::exception {
        public:
            inline ChecksumException(int got, int expected) :
                got(got), expected(expected) {}

            inline const char *what() const noexcept {
                return "invalid checksum";
            }

            int got;
            int expected;
    };

    void Decrypt(uint8_t *dest, uint8_t *src, size_t length);
    void Encrypt(uint8_t *dest, uint8_t *src, size_t length);
    uint32_t GenerateToken();
    void GenerateCookie();
    uint16_t GetCookie(uint32_t address);

    extern uint16_t port;
    extern uint32_t token;
    extern uint16_t cookies[2][256];
    extern void (*HandleQuery)(SOCKET instance, sockaddr_in client, uint8_t *data, size_t size);

    const char *GenerateAuth(uint8_t *index);
    void GenerateAuthKey(char[260], const char *);
    bool CheckAuth(uint8_t index, const char *auth);

    enum {
        AUTH_TYPE_INVALID,
        AUTH_TYPE_PLAYER,
        AUTH_TYPE_NPC
    };

    struct Packet {
        enum {
            VEHICLE_SYNC = 200,
            RCON_COMMAND,
            RCON_RESPONCE,
            AIM_SYNC,
            WEAPONS_UPDATE,
            STATS_UPDATE,
            BULLET_SYNC,
            PLAYER_SYNC,
            MARKERS_SYNC,
            UNOCCUPIED_SYNC,
            TRAILER_SYNC,
            PASSENGER_SYNC,
            SPECTATOR_SYNC,
        };
    };

    struct RPC {
        enum {
            CLICK_PLAYER = 23,
            CLIENT_JOIN = 25,
            ENTER_VEHICLE = 26,
            ENTER_EDIT_OBJECT = 27,
            SCRIPT_CASH = 31,
            SERVER_COMMAND = 50,
            SPAWN = 52,
            DEATH = 53,
            NPC_JOIN = 54,
            DIALOG_RESPONSE = 62,
            CLICK_TEXT_DRAW = 83,
            SCM_EVENT = 96,
            WEAPON_PICKUP_DESTROY = 97,
            CHAT = 101,
            SRV_NET_STATS = 102,
            CLIENT_CHECK = 103,
            DAMAGE_VEHICLE = 106,
            GIVE_TAKE_DAMAGE = 115,
            EDIT_ATTACHED_OBJECT = 116,
            EDIT_OBJECT = 117,
            SET_INTERIOR_ID = 118,
            MAP_MARKER = 119,
            REQUEST_CLASS = 128,
            REQUEST_SPAWN = 129,
            CONNECTION_REJECTED = 130,
            PICKED_UP_PICKUP = 131,
            MENU_SELECT = 132,
            VEHICLE_DESTROYED = 136,
            MENU_QUIT = 140,
            EXIT_VEHICLE = 154,
            UPDATE_SCORES_PINGS_IPS = 155,
            SET_PLAYER_NAME = 11,
            SET_PLAYER_POS = 12,
            SET_PLAYER_POS_FIND_Z = 13,
            SET_PLAYER_HEALTH = 14,
            TOGGLE_PLAYER_CONTROLLABLE = 15,
            PLAY_SOUND = 16,
            SET_PLAYER_WORLD_BOUNDS = 17,
            GIVE_PLAYER_MONEY = 18,
            SET_PLAYER_FACING_ANGLE = 19,
            RESET_PLAYER_MONEY = 20,
            RESET_PLAYER_WEAPONS = 21,
            GIVE_PLAYER_WEAPON = 22,
            SET_VEHICLE_PARAMS_EX = 24,
            CANCEL_EDIT = 28,
            SET_PLAYER_TIME = 29,
            TOGGLE_CLOCK = 30,
            WORLD_PLAYER_ADD = 32,
            SET_PLAYER_SHOP_NAME = 33,
            SET_PLAYER_SKILL_LEVEL = 34,
            SET_PLAYER_DRUNK_LEVEL = 35,
            CREATE3D_TEXT_LABEL = 36,
            DISABLE_CHECKPOINT = 37,
            SET_RACE_CHECKPOINT = 38,
            DISABLE_RACE_CHECKPOINT = 39,
            GAME_MODE_RESTART = 40,
            PLAY_AUDIO_STREAM = 41,
            STOP_AUDIO_STREAM = 42,
            REMOVE_BUILDING_FOR_PLAYER = 43,
            CREATE_OBJECT = 44,
            SET_OBJECT_POS = 45,
            SET_OBJECT_ROT = 46,
            DESTROY_OBJECT = 47,
            DEATH_MESSAGE = 55,
            SET_PLAYER_MAP_ICON = 56,
            REMOVE_VEHICLE_COMPONENT = 57,
            UPDATE3D_TEXT_LABEL = 58,
            CHAT_BUBBLE = 59,
            SOMEUPDATE = 60,
            SHOW_DIALOG = 61,
            DESTROY_PICKUP = 63,
            LINK_VEHICLE_TO_INTERIOR = 65,
            SET_PLAYER_ARMOUR = 66,
            SET_PLAYER_ARMED_WEAPON = 67,
            SET_SPAWN_INFO = 68,
            SET_PLAYER_TEAM = 69,
            PUT_PLAYER_IN_VEHICLE = 70,
            REMOVE_PLAYER_FROM_VEHICLE = 71,
            SET_PLAYER_COLOR = 72,
            DISPLAY_GAME_TEXT = 73,
            FORCE_CLASS_SELECTION = 74,
            ATTACH_OBJECT_TO_PLAYER = 75,
            INIT_MENU = 76,
            SHOW_MENU = 77,
            HIDE_MENU = 78,
            CREATE_EXPLOSION = 79,
            SHOW_PLAYER_NAME_TAG_FOR_PLAYER = 80,
            ATTACH_CAMERA_TO_OBJECT = 81,
            INTERPOLATE_CAMERA = 82,
            SET_OBJECT_MATERIAL = 84,
            GANG_ZONE_STOP_FLASH = 85,
            APPLY_ANIMATION = 86,
            CLEAR_ANIMATIONS = 87,
            SET_PLAYER_SPECIAL_ACTION = 88,
            SET_PLAYER_FIGHTING_STYLE = 89,
            SET_PLAYER_VELOCITY = 90,
            SET_VEHICLE_VELOCITY = 91,
            CLIENT_MESSAGE = 93,
            SET_WORLD_TIME = 94,
            CREATE_PICKUP = 95,
            MOVE_OBJECT = 99,
            ENABLE_STUNT_BONUS_FOR_PLAYER = 104,
            TEXT_DRAW_SET_STRING = 105,
            SET_CHECKPOINT = 107,
            GANG_ZONE_CREATE = 108,
            PLAY_CRIME_REPORT = 112,
            SET_PLAYER_ATTACHED_OBJECT = 113,
            GANG_ZONE_DESTROY = 120,
            GANG_ZONE_FLASH = 121,
            STOP_OBJECT = 122,
            SET_NUMBER_PLATE = 123,
            TOGGLE_PLAYER_SPECTATING = 124,
            PLAYER_SPECTATE_PLAYER = 126,
            PLAYER_SPECTATE_VEHICLE = 127,
            SET_PLAYER_WANTED_LEVEL = 133,
            SHOW_TEXT_DRAW = 134,
            TEXT_DRAW_HIDE = 135,
            SERVER_JOIN = 137,
            SERVER_QUIT = 138,
            INIT_GAME = 139,
            REMOVE_PLAYER_MAP_ICON = 144,
            SET_PLAYER_AMMO = 145,
            SET_GRAVITY = 146,
            SET_VEHICLE_HEALTH = 147,
            ATTACH_TRAILER_TO_VEHICLE = 148,
            DETACH_TRAILER_FROM_VEHICLE = 149,
            SET_WEATHER = 152,
            SET_PLAYER_SKIN = 153,
            SET_PLAYER_INTERIOR = 156,
            SET_PLAYER_CAMERA_POS = 157,
            SET_PLAYER_CAMERA_LOOK_AT = 158,
            SET_VEHICLE_POS = 159,
            SET_VEHICLE_Z_ANGLE = 160,
            SET_VEHICLE_PARAMS_FOR_PLAYER = 161,
            SET_CAMERA_BEHIND_PLAYER = 162,
            WORLD_PLAYER_REMOVE = 163,
            WORLD_VEHICLE_ADD = 164,
            WORLD_VEHICLE_REMOVE = 165,
            WORLD_PLAYER_DEATH = 166,
        };
    };
};