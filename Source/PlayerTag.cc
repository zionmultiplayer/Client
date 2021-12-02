#include "Zion/PlayerTag.hh"
#include "Zion/Client.hh"
#include "ImGui/imgui.h"
#include "Game/CSprite.h"
#include "Game/CCamera.h"

static inline float GetDistance(Zion::Vector3F a, Zion::Vector3F b)
{
    return sqrtf(
        (b.x - a.x) * (b.x - a.x) +
        (b.y - a.y) * (b.y - a.y) +
        (b.z - a.z) * (b.z - a.z));
}

static inline RwV3d Get3DTo2D(RwV3d position)
{
    RwV3d rwOut;
    float outWidth, outHeight;
    CSprite::CalcScreenCoors(position, &rwOut, &outWidth, &outHeight, true, true);
    return rwOut;
}

static inline float GetDistanceFromCamera(Zion::RemotePlayer *remotePlayer)
{
    CVector cameraPosition = TheCamera.GetPosition();
    CVector remotePlayerPosition = remotePlayer->ped->GetPosition();

    return GetDistance(
        {cameraPosition.x, cameraPosition.y, cameraPosition.z},
        {remotePlayerPosition.x, remotePlayerPosition.y, remotePlayerPosition.z});
}

void Zion::PlayerTag::Render()
{
    if(show == false)
        return;

    for(size_t index = 0; index < Client::players.GetLength(); index++)
    {
        RemotePlayer *remotePlayer = Client::players[index];
        if(remotePlayer != nullptr)
        {
            float dfc = GetDistanceFromCamera(remotePlayer);
            if(dfc > 30.0F)
                return;

            float health = remotePlayer->ped->m_fHealth;
            if(health > 100.0F)
                health = 100.0F;
            else if(health < 0.0F)
                health = 0.0F;

            float armour = remotePlayer->ped->m_fArmour;
            if(armour > 100.0F)
                armour = 100.0F;
            else if(armour < 0.0F)
                armour = 0.0F;

            RwV3d position;
            remotePlayer->ped->GetBonePosition(position, 8, false);
            position = Get3DTo2D(position);
            position.y -= 150.0F / dfc;
            position.x -= 30.0F;
     
            ImGui::GetBackgroundDrawList()->AddRectFilled(
                ImVec2(position.x - 1.0F, position.y - 1.0F), ImVec2(position.x + 61.0F, position.y + 9.0F), ImColor(0, 0, 0, 255));
        
            ImGui::GetBackgroundDrawList()->AddRectFilled(
                ImVec2(position.x, position.y), ImVec2(position.x + 60.0F, position.y + 8.0F), ImColor(155, 0, 0, 255));

            ImGui::GetBackgroundDrawList()->AddRectFilled(
                ImVec2(position.x, position.y), ImVec2(position.x + (health * 0.6), position.y + 8.0F), ImColor(255, 0, 0, 255));

            if(armour > 0.0F)
            {
                position.y -= 10.0F + (75.0F / dfc);

                ImGui::GetBackgroundDrawList()->AddRectFilled(
                    ImVec2(position.x - 1.0F, position.y - 1.0F), ImVec2(position.x + 61.0F, position.y + 9.0F), ImColor(0, 0, 0, 255));
            
                ImGui::GetBackgroundDrawList()->AddRectFilled(
                    ImVec2(position.x, position.y), ImVec2(position.x + 60.0F, position.y + 8.0F), ImColor(155, 155, 155, 255));

                ImGui::GetBackgroundDrawList()->AddRectFilled(
                    ImVec2(position.x, position.y), ImVec2(position.x + (armour * 0.6F), position.y + 8.0F), ImColor(255, 255, 255, 255));
            }

            position.y -= 10.0F + (75.0F / dfc);

            ImGui::GetBackgroundDrawList()->AddText(
                ImGui::GetFont(), 14.0F, ImVec2(position.x, position.y),
                ImColor(remotePlayer->color), remotePlayer->nickname);
        }
    }
}

bool Zion::PlayerTag::show = true;