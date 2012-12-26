
#include "ScriptPCH.h"


//This script will reset the winners and loosers cooldowns at the end of the duel
class reset_duel_cooldowns : public PlayerScript
{
    public:
        reset_duel_cooldowns() : PlayerScript("reset_duel_cooldowns") {}

    void OnDuelEnd(Player* winner, Player* looser, DuelCompleteType type)
    {
        winner->RemoveArenaSpellCooldowns();
        looser->RemoveArenaSpellCooldowns();
    }
};

enum ZoneId
{
    WETLANDS = 11,
};

enum AreaId
{
    THE_FORBIDDEN_SEA = 2402
};
//This script will make a specific zone a sanctuary
class set_sanctuary : public PlayerScript
{
    public:
        set_sanctuary() : PlayerScript("set_sanctuary") {}

    void OnUpdateZone(Player* player, uint32 newZone, uint32 newArea)
    {
        if (newZone == WETLANDS && newArea == THE_FORBIDDEN_SEA)
        {
            player->SetByteFlag(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_FLAG_SANCTUARY);
            player->pvpInfo.inNoPvPArea = true;
            player->CombatStopWithPets();
        }
    }
};

//This script will disable duels in specific zone and area
class disable_duel_at_location : public PlayerScript
{
    public:
        disable_duel_at_location() : PlayerScript("disable_duel_at_location") {}

    void OnDuelRequest(Player* target, Player* challenger)
    {
        if (target->GetZoneId() == WETLANDS && target->GetAreaId() == THE_FORBIDDEN_SEA)
        {
            challenger->DuelComplete(DUEL_INTERRUPTED);
            challenger->GetSession()->SendNotification("You cannot not duel here!");
        }
    }
};

// Reward players with 5 Glory points on honor kill
class glory_on_hk : public PlayerScript
{
    public:
        glory_on_hk() : PlayerScript("glory_on_hk") {}

    void OnPVPKill(Player* killer, Player* killed)
    {
        killer->RewardGlory(5, Player::PVP_HK);
    }
};

void AddSC_player_scripts()
{
    new reset_duel_cooldowns;
    new set_sanctuary;
    new disable_duel_at_location;
    new glory_on_hk;
}