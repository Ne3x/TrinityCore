#include "ScriptPCH.h"

enum Quests
{
    QUEST_COMPANION = 80001
};

class npc_azeroth_warper_gossip : public CreatureScript
{
    public:
        npc_azeroth_warper_gossip(): CreatureScript("npc_azeroth_warper_gossip"){}

        bool OnGossipHello(Player* pPlayer, Creature* pCreature)
        {
            if (pPlayer->isInCombat())
            {
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->MonsterWhisper("You are in combat!", pPlayer->GetGUID());
                return true;
            }

            if (pPlayer->GetQuestStatus(QUEST_COMPANION) == QUEST_STATUS_NONE || pPlayer->GetQuestStatus(QUEST_COMPANION) == QUEST_STATUS_INCOMPLETE)
            {
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->MonsterWhisper("You must complete \'Your Companion\' quest in order to use my services.", pPlayer->GetGUID());
                return true;
            }
            else
            {
                pPlayer->PrepareQuestMenu(pCreature->GetGUID());
                if (pPlayer->getLevel() <= 6)
                {
                    switch (pPlayer->getRace())
                    {
                        case RACE_HUMAN:
                            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Warp me to Elwynn Forest", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                            break;

                        case RACE_DWARF:
                        case RACE_GNOME:
                             pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Warp me to Dun Morogh", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                             break;

                        case RACE_NIGHTELF:
                             pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Warp me to Teldrassil", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                             break;

                        case RACE_DRAENEI:
                              pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Warp me to Azuremyst Isle", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
                              break;

                        case RACE_ORC:
                        case RACE_TROLL:
                             pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Warp me to Durotar", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
                             break;

                        case RACE_TAUREN:
                             pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Warp me to Mulgore", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5);
                             break;

                        case RACE_UNDEAD_PLAYER:
                             pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Warp me to Trisfal Glades", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+6);
                             break;

                        case RACE_BLOODELF:
                             pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Warp me to Eversong Woods", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+7);
                             break;

                        default:
                        break;
                    }
                }
                else
                {
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Warp me to Custom Town" , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+8);
                }
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I am not ready to leave yet." , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+9);
                pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
                return true;
            }
        }

        bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 uiAction)
        {
            pPlayer->PlayerTalkClass->ClearMenus();

            switch(uiAction)
            {

                case GOSSIP_ACTION_INFO_DEF:
                    pPlayer->removeSpell(48756);
                    pPlayer->TeleportTo(0, -8949.950195f, -132.492996f, 83.531197f, 0.0000f);
                    pPlayer->CLOSE_GOSSIP_MENU();
                break;

                case GOSSIP_ACTION_INFO_DEF+1:
                    pPlayer->removeSpell(48756);
                    pPlayer->TeleportTo(0, -6240.319824f, 331.032990f, 382.757996f, 6.177160f);
                    pPlayer->CLOSE_GOSSIP_MENU();
                break;

                case GOSSIP_ACTION_INFO_DEF+2:
                    pPlayer->removeSpell(48756);
                    pPlayer->TeleportTo(1, 10311.299805f, 832.463013f, 1326.407227f, 5.696320f);
                    pPlayer->CLOSE_GOSSIP_MENU();
                break;

                case GOSSIP_ACTION_INFO_DEF+3:
                    pPlayer->removeSpell(48756);
                    pPlayer->TeleportTo(530, -3961.639893f, -13931.200195f, 100.613525f, 2.083640f);
                    pPlayer->CLOSE_GOSSIP_MENU();
                break;

                case GOSSIP_ACTION_INFO_DEF+4:
                    pPlayer->removeSpell(48756);
                    pPlayer->TeleportTo(1, -618.518005f, -4251.669922f, 38.717999f, 0.000000f);
                    pPlayer->CLOSE_GOSSIP_MENU();
                break;

                case GOSSIP_ACTION_INFO_DEF+5:
                    pPlayer->removeSpell(48756);
                    pPlayer->TeleportTo(1, -2917.580078f, -257.980011f, 52.996799f, 0.000000f);
                    pPlayer->CLOSE_GOSSIP_MENU();
                break;

                case GOSSIP_ACTION_INFO_DEF+6:
                    pPlayer->removeSpell(48756);
                    pPlayer->TeleportTo(0, 1676.709961f, 1678.310059f, 121.66998f, 2.705260f);
                    pPlayer->CLOSE_GOSSIP_MENU();
                break;

                case GOSSIP_ACTION_INFO_DEF+7:
                    pPlayer->removeSpell(48756);
                    pPlayer->TeleportTo(530, 10349.599609f, -6357.290039f, 33.402599f, 5.316050f);
                    pPlayer->CLOSE_GOSSIP_MENU();
                break;

                case GOSSIP_ACTION_INFO_DEF+8:
                    pPlayer->removeSpell(48756);
                    pPlayer->TeleportTo(0, -7634.04f, -4565.26f, 131.41f, 3.21f);
                    pPlayer->CLOSE_GOSSIP_MENU();
                break;

                case GOSSIP_ACTION_INFO_DEF+9:
                    pPlayer->CLOSE_GOSSIP_MENU();
                break;

                default:
                break;
            }
            return true;
        }
};

class npc_outland_warper_gossip : public CreatureScript
{
    public:
        npc_outland_warper_gossip(): CreatureScript("npc_outland_warper_gossip"){}

        bool OnGossipHello(Player* pPlayer, Creature* pCreature)
        {
            if (pPlayer->isInCombat())
            {
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->MonsterWhisper("You are in combat!", pPlayer->GetGUID());
                return true;
            }

            if (pPlayer->getLevel() < 58)
            {
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->MonsterWhisper("You must be atleast level 58 in order to use my services", pPlayer->GetGUID());
                return true;
            }

            if (pPlayer->GetQuestStatus(QUEST_COMPANION) == QUEST_STATUS_INCOMPLETE)
            {
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->MonsterWhisper("You must complete \'Your Companion\' quest in order to use my services.", pPlayer->GetGUID());
                return true;
            }
            else
            {
                pPlayer->PrepareQuestMenu(pCreature->GetGUID());
                if (pPlayer->getLevel() >= 58)
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Warp me to The Dark Portal" , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                if (pPlayer->getLevel() >= 65)
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Warp me to Shattrath" , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I am not ready to leave yet." , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
                return true;
            }
        }

        bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 uiAction)
        {
            pPlayer->PlayerTalkClass->ClearMenus();

            switch(uiAction)
            {

                case GOSSIP_ACTION_INFO_DEF:
                    pPlayer->removeSpell(48756);
                    pPlayer->TeleportTo(0, -11811.272461f, -3190.375244f, -30.705469f, 3.420288f);
                    pPlayer->CLOSE_GOSSIP_MENU();
                break;

                case GOSSIP_ACTION_INFO_DEF+1:
                    pPlayer->removeSpell(48756);
                    pPlayer->TeleportTo(530, -1839.831299f, 5382.478516f, -12.428227f, 2.008222f);
                    pPlayer->CLOSE_GOSSIP_MENU();
                break;

                case GOSSIP_ACTION_INFO_DEF+2:
                    pPlayer->CLOSE_GOSSIP_MENU();
                break;

                default:
                break;
            }
            return true;
        }
};

class npc_northrend_warper_gossip : public CreatureScript
{
    public:
        npc_northrend_warper_gossip(): CreatureScript("npc_northrend_warper_gossip"){}

        bool OnGossipHello(Player* pPlayer, Creature* pCreature)
        {
            if (pPlayer->isInCombat())
            {
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->MonsterWhisper("You are in combat!", pPlayer->GetGUID());
                return true;
            }

            if (pPlayer->getLevel() < 68)
            {
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->MonsterWhisper("You must be atleast level 68 in order to use my services", pPlayer->GetGUID());
                return true;
            }

            if (pPlayer->GetQuestStatus(QUEST_COMPANION) == QUEST_STATUS_INCOMPLETE)
            {
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->MonsterWhisper("You must complete \'Your Companion\' quest in order to use my services.", pPlayer->GetGUID());
                return true;
            }
            else
            {
                pPlayer->PrepareQuestMenu(pCreature->GetGUID());
                if (pPlayer->getLevel() >= 68)
                {
                    if (pPlayer->GetTeam() == HORDE)
                    {
                        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Take me to Borean Tundra" , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Take me to Howling Fjord" , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                    }
                    else
                    {
                        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Take me to Borean Tundra" , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Take me to Howling Fjord" , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
                    }
                }
                if (pPlayer->getLevel() >= 75)
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Take me to Dalaran" , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);

                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I am not ready to leave yet." , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5);
                pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
                return true;
            }
        }

        bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 uiAction)
        {
            pPlayer->PlayerTalkClass->ClearMenus();

            switch(uiAction)
            {

                case GOSSIP_ACTION_INFO_DEF:
                    pPlayer->removeSpell(48756);
                    pPlayer->TeleportTo(571, 2743.824463f, 6100.675781f, 77.335289f, 0.752949f);
                    pPlayer->CLOSE_GOSSIP_MENU();
                break;

                case GOSSIP_ACTION_INFO_DEF+1:
                    pPlayer->removeSpell(48756);
                    pPlayer->TeleportTo(571, 1985.0594f, -6219.0757f, 7.7398f, 0.3681f);
                    pPlayer->CLOSE_GOSSIP_MENU();
                break;

                case GOSSIP_ACTION_INFO_DEF+2:
                    pPlayer->removeSpell(48756);
                    pPlayer->TeleportTo(571, 2261.964f, 5254.692f, 7.164f, 5.866f);
                    pPlayer->CLOSE_GOSSIP_MENU();
                break;

                case GOSSIP_ACTION_INFO_DEF+3:
                    pPlayer->removeSpell(48756);
                    pPlayer->TeleportTo(571, 590.4257f, -5097.2285f, 5.2604f, 1.3969f);
                    pPlayer->CLOSE_GOSSIP_MENU();
                break;

                case GOSSIP_ACTION_INFO_DEF+4:
                    pPlayer->removeSpell(48756);
                    pPlayer->TeleportTo(571, 5804.1499f, 624.771f, 647.767f, 1.64f);
                    pPlayer->CLOSE_GOSSIP_MENU();
                break;

                case GOSSIP_ACTION_INFO_DEF+5:
                    pPlayer->CLOSE_GOSSIP_MENU();
                break;

                default:
                break;
            }
            return true;
        }
};

void AddSC_npc_warper_gossips()
{
    new npc_azeroth_warper_gossip();
    new npc_outland_warper_gossip();
    new npc_northrend_warper_gossip();
}