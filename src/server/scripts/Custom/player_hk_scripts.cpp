/*
    This script will reset the winners and loosers cooldowns at the end of the duel
*/
#include "ScriptPCH.h"

class player_hk_scripts : public PlayerScript
{
    public:
        player_hk_scripts() : PlayerScript("player_hk_scripts") {}

    void OnPVPKill(Player* killer, Player* killed)
    {
        killer->RewardGlory(5, Player::PVP_HK);
    }
};

void AddSC_player_HK_scripts()
{
    new player_hk_scripts;
}