#include "ScriptPCH.h"

/***********************/
/* NPC Mini Pet Gossip */
/***********************/
enum Quests
{
    QUEST_STARTING       = 70000,
    QUEST_WELCOME        = 80000,
    QUEST_TO_AZEROTH     = 80003,
    QUEST_TO_OUTLANDS    = 80004,
    QUEST_TO_NORTHREND   = 80005,
    QUEST_TO_CUSTOM_TOWN = 80006,
};

//Custom Function to check if player has completed all required quests.
bool GetRequiredQuestStatus(Player* player)
{
    if (player->GetQuestStatus(QUEST_TO_AZEROTH) == QUEST_STATUS_REWARDED || player->GetQuestStatus(QUEST_TO_OUTLANDS) == QUEST_STATUS_REWARDED || 
        player->GetQuestStatus(QUEST_TO_NORTHREND) == QUEST_STATUS_REWARDED || player->GetQuestStatus(QUEST_TO_CUSTOM_TOWN) == QUEST_STATUS_REWARDED)
        return true;
    else
        return false;
}

class npc_mini_pet_gossip : public CreatureScript
{
    public:
        npc_mini_pet_gossip(): CreatureScript("npc_mini_pet_gossip"){}

        bool OnGossipHello(Player* player, Creature* creature)
        {
            if (player->isInCombat())
            {
                player->CLOSE_GOSSIP_MENU();
                creature->MonsterWhisper("You are in combat!", player->GetGUID());
                return false;
            }
                else
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "Train me my Class Spells" , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "Reset my Talents" , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);                    
                    if (GetRequiredQuestStatus(player) || player->getLevel() == 80)
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Take me to Custom Town", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+15);
                    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                    return true;
                }
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 uiAction)
        {
            player->PlayerTalkClass->ClearMenus();

            switch(uiAction)
            {
                case GOSSIP_ACTION_INFO_DEF:
                    switch (player->getClass())
                    {
                        case CLASS_DEATH_KNIGHT:
                            if (player->getLevel() >= 55)
                            {
                                player->learnSpell(48778, false);
                                player->learnSpell(53428, false);
                                player->learnSpell(50977, false);
                                player->learnSpell(48743, false);
                            }
                            if (player->getLevel() >= 61)
                            {
                                player->learnSpell(3714, false);
                            }
                            if (player->getLevel() >= 65)
                            {
                                player->learnSpell(57330, false);
                            }
                            if (player->getLevel() >= 67)
                            {
                                player->learnSpell(56815, false);
                            }
                            break;

                        case CLASS_WARLOCK:
                            if (player->getLevel() >= 20)
                            {
                                player->learnSpell(5784, false);
                            }
                            if (player->getLevel() >= 40)
                            {
                                player->learnSpell(23161, false);
                            }
                            break;

                        case CLASS_PALADIN:
                            if (player->getFaction() == ALLIANCE)
                            {
                                if (player->getLevel() >= 20)
                                {
                                    player->learnSpell(13819, false);
                                }
                                if (player->getLevel() >= 40)
                                {
                                    player->learnSpell(23214, false);
                                }
                            }
                            if (player->getFaction() == HORDE)
                            {
                                if (player->getLevel() >= 20)
                                {
                                    player->learnSpell(34769, false);
                                }
                                if (player->getLevel() >= 40)
                                {
                                    player->learnSpell(34767, false);
                                }
                            }
                            break;

                        case CLASS_DRUID:
                            if(player->getLevel() >= 60)
                            {
                                player->learnSpell(33943, false);
                            }
                            if(player->getLevel() >= 71)
                            {
                                player->learnSpell(40120, false);
                            }
                            break;

                        default:
                            break;
                    }
                    player->GetSession()->SendTrainerList(creature->GetGUID());
                    break;

                case GOSSIP_ACTION_INFO_DEF+1:
                    player->SendTalentWipeConfirm(creature->GetGUID());
                    player->CLOSE_GOSSIP_MENU();
                    break;

                case GOSSIP_ACTION_INFO_DEF+2:
                    player->GetSession()->SendListInventory(creature->GetGUID());
                    break;

                case GOSSIP_ACTION_INFO_DEF+15:
                    player->TeleportTo(0, -7634.04f, -4565.26f, 131.41f, 3.21f);
                    player->CLOSE_GOSSIP_MENU();
                    break;

                default:
                    break;
            }
            return true;
        }
};

/***************************/
/* NPC Level Master Gossip */
/***************************/

class npc_level_master_gossip : public CreatureScript
{
    public:
        npc_level_master_gossip(): CreatureScript("npc_level_master_gossip"){}

        bool OnGossipHello(Player* player, Creature* creature)
        {
            if (player->isInCombat())
            {
                player->CLOSE_GOSSIP_MENU();
                creature->MonsterWhisper("You are in combat!", player->GetGUID());
                return false;
            }
            else
            {
                player->PrepareQuestMenu(creature->GetGUID());
                player->SendPreparedQuest(creature->GetGUID());
                if ((player->GetQuestStatus(QUEST_WELCOME) == QUEST_STATUS_REWARDED) && (!player->HasAura(48756)))
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Would you like to be leveled up to the level of your choice?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);                    
                }
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                return true;
            }
        }

        //This function is called when the player clicks an option on the gossip menubool
        bool OnGossipSelect(Player* player, Creature* creature, uint32 uiSender, uint32 uiAction )
        {
            switch(uiAction)
            {
                case GOSSIP_ACTION_INFO_DEF:
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_CHAT, " - Yes, please", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1, "", 0, true);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, " - No, thanks", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                    break;

                case GOSSIP_ACTION_INFO_DEF+2:
                    player->CastSpell(player, 48756, true);
                    player->CLOSE_GOSSIP_MENU();
                    break;
            }
            return true;
        }

        bool OnGossipSelectCode(Player* player, Creature* creature, uint32 uiSender, uint32 uiAction, const char * sCode )
        {
            player->PlayerTalkClass->ClearMenus();
            if (uiSender == GOSSIP_SENDER_MAIN)
            {
                switch (uiAction)
                {
                    case GOSSIP_ACTION_INFO_DEF+1:
                        int level = atoi(sCode);
                        if ((level >= 2 && level <= 80) && (player->getLevel() < level))
                        {
                            player->GiveLevel(level);
                            player->CastSpell(player, 48756, true);
                            player->CLOSE_GOSSIP_MENU();
                        }
                        else
                        {
                            creature->MonsterWhisper("The value must be between 2-80 and greater than your current level", player->GetGUID());
                            player->CLOSE_GOSSIP_MENU();
                        }
                        return true;
                        break;
                }
            }
            return false;
        }
};

/**************************/
/* NPC Card Master Gossip */
/**************************/
enum Cards
{
    FIRE_CARD_1 = 70001,
    FIRE_CARD_2 = 70002,
    FIRE_CARD_3 = 70003,
    FIRE_CARD_4 = 70004,
    FIRE_CARD_5 = 70005,
    FIRE_CARD_6 = 70006,
    FIRE_CARD_7 = 70007,
    FIRE_CARD_8 = 70008,
    FIRE_CARD_9 = 70009,
    MINOR_DECK  = 70010,
    MEDIUM_DECK = 70011,
    MAJOR_DECK  = 70012
};

class npc_card_master_gossip : public CreatureScript
{
    public:
        npc_card_master_gossip(): CreatureScript("npc_card_master_gossip"){}

        bool OnGossipHello(Player* player, Creature* creature)
        {
            if (player->isInCombat())
            {
                player->CLOSE_GOSSIP_MENU();
                creature->MonsterWhisper("You are in combat!", player->GetGUID());
                return true;
            }

            if (player->getLevel() != 80)
            {
                player->CLOSE_GOSSIP_MENU();
                creature->MonsterWhisper("You must be level 80!", player->GetGUID());
                return true;
            }
            else
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_OPTION_QUESTGIVER, "Quests", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Combine my Fire Cards into a Deck", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Tell me more about Fire Decks", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                return true;
            }
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 uiAction)
        {
            player->PlayerTalkClass->ClearMenus();

            switch(uiAction)
            {

                case GOSSIP_ACTION_INFO_DEF:
                    player->PrepareQuestMenu(creature->GetGUID());
                    player->SendPreparedQuest(creature->GetGUID());
                break;

                case GOSSIP_ACTION_INFO_DEF+1:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Create Minor Fire Deck", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Create Medium Fire Deck", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Create Major Fire Deck", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+6);
                    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                break;

                case GOSSIP_ACTION_INFO_DEF+2://Advance Professions
                    player->GetSession()->SendListInventory(creature->GetGUID());
                break;

                case GOSSIP_ACTION_INFO_DEF+3:
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterWhisper("There are three types of deck that can be created with cards of Fire. Minor deck which consists 'Ace through Three of Fire', medium deck which consists of 'Ace through Six of Fire' and major deck which consists of 'Ace through Nine of Fire'", player->GetGUID());
                    creature->MonsterWhisper("Cards can be found in the different Icecrown Heroic Dungeons or Raids. Once you collect a specific amount of cards talk to me in order to combine them into a deck.", player->GetGUID());
                    creature->MonsterWhisper("Once you complete a deck, I will reward your efforts with appropriate reward.", player->GetGUID());
                break;

                        case GOSSIP_ACTION_INFO_DEF+4://Minor Deck
                    player->CLOSE_GOSSIP_MENU();
                    if (player->HasItemCount(FIRE_CARD_1,1) && player->HasItemCount(FIRE_CARD_2,1) && player->HasItemCount(FIRE_CARD_3,1))
                    {
                        player->DestroyItemCount(FIRE_CARD_1, 1, true);
                        player->DestroyItemCount(FIRE_CARD_2, 1, true);
                        player->DestroyItemCount(FIRE_CARD_3, 1, true);
                        player->StoreNewItemInBestSlots(MINOR_DECK, 1);
                        creature->MonsterWhisper("Minor Deck has been added to your inventory, use it wisely.", player->GetGUID());
                    }
                    else
                        creature->MonsterWhisper("You don't have the right cards in your inventory.", player->GetGUID());
                break;

                case GOSSIP_ACTION_INFO_DEF+5://Medium Deck
                    player->CLOSE_GOSSIP_MENU();
                    if (player->HasItemCount(FIRE_CARD_1,1) && player->HasItemCount(FIRE_CARD_2,1) && player->HasItemCount(FIRE_CARD_3,1) && player->HasItemCount(FIRE_CARD_4,1) &&
                    player->HasItemCount(FIRE_CARD_5,1) && player->HasItemCount(FIRE_CARD_6,1))
                    {
                        player->DestroyItemCount(FIRE_CARD_1, 1, true);
                        player->DestroyItemCount(FIRE_CARD_2, 1, true);
                        player->DestroyItemCount(FIRE_CARD_3, 1, true);
                        player->DestroyItemCount(FIRE_CARD_4, 1, true);
                        player->DestroyItemCount(FIRE_CARD_5, 1, true);
                        player->DestroyItemCount(FIRE_CARD_6, 1, true);
                        player->StoreNewItemInBestSlots(MEDIUM_DECK, 1);
                        creature->MonsterWhisper("Medium Deck has been added to your inventory, use it wisely.", player->GetGUID());
                    }
                    else
                        creature->MonsterWhisper("You don't have the right cards in your inventory.", player->GetGUID());
                break;

                case GOSSIP_ACTION_INFO_DEF+6://Major Deck
                    player->CLOSE_GOSSIP_MENU();

                    if (player->HasItemCount(FIRE_CARD_1,1) && player->HasItemCount(FIRE_CARD_2,1) && player->HasItemCount(FIRE_CARD_3,1) && player->HasItemCount(FIRE_CARD_4,1) &&
                    player->HasItemCount(FIRE_CARD_5,1) && player->HasItemCount(FIRE_CARD_6,1) && player->HasItemCount(FIRE_CARD_7,1) && player->HasItemCount(FIRE_CARD_8,1) &&
                    player->HasItemCount(FIRE_CARD_9,1))
                    {
                        player->DestroyItemCount(FIRE_CARD_1, 1, true);
                        player->DestroyItemCount(FIRE_CARD_2, 1, true);
                        player->DestroyItemCount(FIRE_CARD_3, 1, true);
                        player->DestroyItemCount(FIRE_CARD_4, 1, true);
                        player->DestroyItemCount(FIRE_CARD_5, 1, true);
                        player->DestroyItemCount(FIRE_CARD_6, 1, true);
                        player->DestroyItemCount(FIRE_CARD_7, 1, true);
                        player->DestroyItemCount(FIRE_CARD_8, 1, true);
                        player->DestroyItemCount(FIRE_CARD_9, 1, true);
                        player->StoreNewItemInBestSlots(MAJOR_DECK, 1);
                        creature->MonsterWhisper("Major Deck has been added to your inventory, use it wisely.", player->GetGUID());
                    }
                    else
                        creature->MonsterWhisper("You don't have the right cards in your inventory.", player->GetGUID());
                break;


                default:
                break;
            }
            return true;
        }
};

/**************************/
/* NPC Raid Master Gossip */
/**************************/

enum Events
{
        RAID_EVENT_BLACKWING_LAIR        = 104,
        RAID_EVENT_THE_EYE               = 105,
        RAID_EVENT_BLACK_TEMPLE          = 106,
        RAID_EVENT_ONYXIAS_LAIR 	     = 107,
        RAID_EVENT_VAULT_OF_ARCHAVON     = 108,
        RAID_EVENT_ICECROWN_CITADEL      = 109,
        RAID_EVENT_TRIAL_OF_THE_CRUSADER = 110
};

class npc_raid_master_gossip : public CreatureScript
{
    public:
        npc_raid_master_gossip(): CreatureScript("npc_raid_master_gossip"){}

        bool OnGossipHello(Player* player, Creature* creature)
        {
            if (player->isInCombat())
            {
                player->CLOSE_GOSSIP_MENU();
                creature->MonsterWhisper("You are in combat!", player->GetGUID());
                return true;
            }

            if (player->getLevel() != 80)
            {
                player->CLOSE_GOSSIP_MENU();
                creature->MonsterWhisper("You must be level 80!", player->GetGUID());
                return true;
            }

            else
            {
                    player->PrepareQuestMenu(creature->GetGUID());
                    player->SendPreparedQuest(creature->GetGUID());
                    if (sGameEventMgr->IsActiveEvent(RAID_EVENT_BLACKWING_LAIR))
                        player->ADD_GOSSIP_ITEM(GOSSIP_OPTION_QUESTGIVER, "Warp me to Blackwing Lair", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                    if (sGameEventMgr->IsActiveEvent(RAID_EVENT_THE_EYE))
                        player->ADD_GOSSIP_ITEM(GOSSIP_OPTION_QUESTGIVER, "Warp me to Tempest Keep: The Eye", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                    if (sGameEventMgr->IsActiveEvent(RAID_EVENT_BLACK_TEMPLE))
                        player->ADD_GOSSIP_ITEM(GOSSIP_OPTION_QUESTGIVER, "Warp me to Black Temple", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                    if (sGameEventMgr->IsActiveEvent(RAID_EVENT_ONYXIAS_LAIR))
                        player->ADD_GOSSIP_ITEM(GOSSIP_OPTION_QUESTGIVER, "Warp me to Onyxia's Lair", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
                    if (sGameEventMgr->IsActiveEvent(RAID_EVENT_VAULT_OF_ARCHAVON))
                        player->ADD_GOSSIP_ITEM(GOSSIP_OPTION_QUESTGIVER, "Warp me to Vault of Archavon", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
                    if (sGameEventMgr->IsActiveEvent(RAID_EVENT_ICECROWN_CITADEL))
                        player->ADD_GOSSIP_ITEM(GOSSIP_OPTION_QUESTGIVER, "Warp me to Icecrown Citadel", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5);
                    if (sGameEventMgr->IsActiveEvent(RAID_EVENT_TRIAL_OF_THE_CRUSADER))
                        player->ADD_GOSSIP_ITEM(GOSSIP_OPTION_QUESTGIVER, "Warp me to Trial of the Crusader", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+6);
                    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                    return true;
            }
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 uiAction)
        {
            player->PlayerTalkClass->ClearMenus();

            switch(uiAction)
            {

                case GOSSIP_ACTION_INFO_DEF:
                    player->TeleportTo(229, 161.30f, -474.97f, 116.84f, 6.27f);
                    player->CLOSE_GOSSIP_MENU();
                break;

                case GOSSIP_ACTION_INFO_DEF+1:
                    player->TeleportTo(530, 3088.19f, 1379.46f, 184.91f, 4.61f);
                    player->CLOSE_GOSSIP_MENU();
                break;

                 case GOSSIP_ACTION_INFO_DEF+2:
                    player->TeleportTo(530, -3647.81f, 316.23f, 35.27f, 2.89f);
                    player->CLOSE_GOSSIP_MENU();
                 break;

                case GOSSIP_ACTION_INFO_DEF+3:
                    player->TeleportTo(1, -4738.80f, -3751.05f, 52.41f, 3.20f);
                    player->CLOSE_GOSSIP_MENU();
                break;

                case GOSSIP_ACTION_INFO_DEF+4:
                    player->TeleportTo(571, 5472.83f, 2840.80f, 418.68f, 6.18f);
                    player->CLOSE_GOSSIP_MENU();
                break;

                case GOSSIP_ACTION_INFO_DEF+5:
                    player->TeleportTo(571, 5873.82f, 2110.98f, 636.01f, 3.55f);
                    player->CLOSE_GOSSIP_MENU();
                break;

                case GOSSIP_ACTION_INFO_DEF+6:
                    player->TeleportTo(571, 8515.88f, 629.25f, 547.39f, 1.57f);
                    player->CLOSE_GOSSIP_MENU();
                break;

                default:
                break;
            }
            return true;
        }
};

/**************************/
/* NPC Illusionist Gossip */
/**************************/
enum cost
{
    ILLUSION_COST = 500000, //50 gold
    ILLUSION_SPECIAL_COST = 1000000 //100 gold
};

class npc_illusionist_gossip : public CreatureScript
{
    public:
        npc_illusionist_gossip(): CreatureScript("npc_illusionist_gossip"){}

        bool OnGossipHello(Player* player, Creature* creature)
        {
            if (player->isInCombat())
            {
                player->CLOSE_GOSSIP_MENU();
                creature->MonsterWhisper("You are in combat!", player->GetGUID());
                return false;
            }
            else
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Alliance Illusions", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Horde Illusions", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Special Illusions", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                return true;
            }
        }

        bool IsShapeshifted(Player* player)
        {
            if (player->HasAura(5487, player->GetGUID()) || player->HasAura(9634, player->GetGUID()) || player->HasAura(768, player->GetGUID()) || player->HasAura(24858, player->GetGUID()) ||
            player->HasAura(33891, player->GetGUID()) || player->HasAura(1066, player->GetGUID()) || player->HasAura(783, player->GetGUID()) || player->HasAura(33943, player->GetGUID()) ||
            player->HasAura(40120, player->GetGUID()))
                return true;
            else
                return false;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 uiAction)
        {
            switch(uiAction)
            {
                case GOSSIP_ACTION_INFO_DEF:
                    if (player->GetTeam() == HORDE && player->GetSession()->GetSecurity() != SEC_MODERATOR )
                    {
                        creature->MonsterWhisper("You must be VIP in order to recieve opposite faction illusions", player->GetGUID());
                        player->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        player->PlayerTalkClass->ClearMenus();
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Human Male Illusion :: 50 gold", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+6);
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Human Female Illusion :: 50 gold", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+7);
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Gnome Male Illusion :: 50 gold", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+8);
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Gnome Female Illusion :: 50 gold", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+9);
                        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                    }
                    break;

                case GOSSIP_ACTION_INFO_DEF+1:
                    if (player->GetTeam() == ALLIANCE && player->GetSession()->GetSecurity() != SEC_MODERATOR )
                    {
                        creature->MonsterWhisper("You must be VIP in order to recieve opposite faction illusions", player->GetGUID());
                        player->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        player->PlayerTalkClass->ClearMenus();
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Tauren Male Illusion :: 50 gold", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+10);
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Tauren Female Illusion :: 50 gold", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+11);
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Blood Elf Male Illusion :: 50 gold", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+12);
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Blood Elf Female Illusion :: 50 gold", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+13);
                        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                    }
                    break;

               case GOSSIP_ACTION_INFO_DEF+2:
                        player->PlayerTalkClass->ClearMenus();
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Leeper Gnome Illusion :: 100 gold", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+14);
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Pirate Illusion :: 100 gold", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+15);
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Ninja Illusion :: 100 gold", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+16);
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Skeleton Illusion :: 100 gold", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+17);
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Ghost Illusion :: 100 gold", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+18);
                        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                    break;

                case GOSSIP_ACTION_INFO_DEF+6:
                    if (IsShapeshifted(player))
                    {
                        creature->MonsterWhisper("You can't do this while shapeshifted.", player->GetGUID());
                        player->CLOSE_GOSSIP_MENU();
                    }
                    if (player->HasEnoughMoney(ILLUSION_COST))
                    {
                        player->CastSpell(player, 35466, true);
                        player->ModifyMoney(-ILLUSION_COST);
                        player->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        creature->MonsterWhisper("You don't have enough money to receive an illusion", player->GetGUID());
                        player->CLOSE_GOSSIP_MENU();
                    }
                    break;

                case GOSSIP_ACTION_INFO_DEF+7:
                    if (IsShapeshifted(player))
                    {
                        creature->MonsterWhisper("You can't do this while shapeshifted.", player->GetGUID());
                        player->CLOSE_GOSSIP_MENU();
                    }
                    if (player->HasEnoughMoney(ILLUSION_COST))
                    {
                        player->CastSpell(player, 37805, true);
                        player->ModifyMoney(-ILLUSION_COST);
                        player->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        creature->MonsterWhisper("You don't have enough money to receive an illusion", player->GetGUID());
                        player->CLOSE_GOSSIP_MENU();
                    }
                    break;

                case GOSSIP_ACTION_INFO_DEF+8:
                    if (IsShapeshifted(player))
                    {
                        creature->MonsterWhisper("You can't do this while shapeshifted.", player->GetGUID());
                        player->CLOSE_GOSSIP_MENU();
                    }
                    if (player->HasEnoughMoney(ILLUSION_COST))
                    {
                        player->CastSpell(player, 37808, true);
                        player->ModifyMoney(-ILLUSION_COST);
                        player->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        creature->MonsterWhisper("You don't have enough money to receive an illusion", player->GetGUID());
                        player->CLOSE_GOSSIP_MENU();
                    }
                    break;

                case GOSSIP_ACTION_INFO_DEF+9:
                    if (IsShapeshifted(player))
                    {
                        creature->MonsterWhisper("You can't do this while shapeshifted.", player->GetGUID());
                        player->CLOSE_GOSSIP_MENU();
                    }
                    if (player->HasEnoughMoney(ILLUSION_COST))
                    {
                        player->CastSpell(player, 37809, true);
                        player->ModifyMoney(-ILLUSION_COST);
                        player->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        creature->MonsterWhisper("You don't have enough money to receive an illusion", player->GetGUID());
                        player->CLOSE_GOSSIP_MENU();
                    }
                    break;

                case GOSSIP_ACTION_INFO_DEF+10:
                    if (IsShapeshifted(player))
                    {
                        creature->MonsterWhisper("You can't do this while shapeshifted.", player->GetGUID());
                        player->CLOSE_GOSSIP_MENU();
                    }
                    if (player->HasEnoughMoney(ILLUSION_COST))
                    {
                        player->CastSpell(player, 37810, true);
                        player->ModifyMoney(-ILLUSION_COST);
                        player->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        creature->MonsterWhisper("You don't have enough money to receive an illusion", player->GetGUID());
                        player->CLOSE_GOSSIP_MENU();
                    }
                    break;

                case GOSSIP_ACTION_INFO_DEF+11:
                    if (IsShapeshifted(player))
                    {
                        creature->MonsterWhisper("You can't do this while shapeshifted.", player->GetGUID());
                        player->CLOSE_GOSSIP_MENU();
                    }
                    if (player->HasEnoughMoney(ILLUSION_COST))
                    {
                        player->CastSpell(player, 37811, true);
                        player->ModifyMoney(-ILLUSION_COST);
                        player->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        creature->MonsterWhisper("You don't have enough money to receive an illusion", player->GetGUID());
                        player->CLOSE_GOSSIP_MENU();
                    }
                    break;

                case GOSSIP_ACTION_INFO_DEF+12:
                    if (IsShapeshifted(player))
                    {
                        creature->MonsterWhisper("You can't do this while shapeshifted.", player->GetGUID());
                        player->CLOSE_GOSSIP_MENU();
                    }
                    if (player->HasEnoughMoney(ILLUSION_COST))
                    {
                        player->CastSpell(player, 37807, true);
                        player->ModifyMoney(-ILLUSION_COST);
                        player->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        creature->MonsterWhisper("You don't have enough money to receive an illusion", player->GetGUID());
                        player->CLOSE_GOSSIP_MENU();
                    }
                    break;

                case GOSSIP_ACTION_INFO_DEF+13:
                    if (IsShapeshifted(player))
                    {
                        creature->MonsterWhisper("You can't do this while shapeshifted.", player->GetGUID());
                        player->CLOSE_GOSSIP_MENU();
                    }
                    if (player->HasEnoughMoney(ILLUSION_COST))
                    {
                        player->CastSpell(player, 37806, true);
                        player->ModifyMoney(-ILLUSION_COST);
                        player->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        creature->MonsterWhisper("You don't have enough money to receive an illusion", player->GetGUID());
                        player->CLOSE_GOSSIP_MENU();
                    }
                    break;

                //Leaper Gnome Option 100 Gold
                case GOSSIP_ACTION_INFO_DEF+14:
                    if (IsShapeshifted(player))
                    {
                        creature->MonsterWhisper("You can't do this while shapeshifted.", player->GetGUID());
                        player->CLOSE_GOSSIP_MENU();
                    }
                    if (player->HasEnoughMoney(ILLUSION_SPECIAL_COST))
                    {
                        player->CastSpell(player, 24713, true);
                        player->ModifyMoney(-ILLUSION_SPECIAL_COST);
                        player->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        creature->MonsterWhisper("You don't have enough money to receive an illusion", player->GetGUID());
                        player->CLOSE_GOSSIP_MENU();
                    }
                    break;
                
                //Pirate Costume 100 gold
                case GOSSIP_ACTION_INFO_DEF+15:
                    if (IsShapeshifted(player))
                    {
                        creature->MonsterWhisper("You can't do this while shapeshifted.", player->GetGUID());
                        player->CLOSE_GOSSIP_MENU();
                    }
                    if (player->HasEnoughMoney(ILLUSION_SPECIAL_COST))
                    {
                        if (player->getGender() == GENDER_MALE)
                        {
                            player->CastSpell(player, 24708, true);
                            player->ModifyMoney(-ILLUSION_SPECIAL_COST);
                            player->CLOSE_GOSSIP_MENU();
                        }
                        else
                        {
                            player->CastSpell(player, 24709, true);
                            player->ModifyMoney(-ILLUSION_SPECIAL_COST);
                            player->CLOSE_GOSSIP_MENU();
                        }
                    }
                    else
                    {
                        creature->MonsterWhisper("You can't do this while shapeshifted.", player->GetGUID());
                        player->CLOSE_GOSSIP_MENU();
                    }
                    break;

                //Ninja Costume 100 gold
                case GOSSIP_ACTION_INFO_DEF+16:
                    if (IsShapeshifted(player))
                    {
                        creature->MonsterWhisper("You can't do this while shapeshifted.", player->GetGUID());
                        player->CLOSE_GOSSIP_MENU();
                    }
                    if (player->HasEnoughMoney(ILLUSION_SPECIAL_COST))
                    {
                        if (player->getGender() == GENDER_MALE)
                        {
                            player->CastSpell(player, 24711, true);
                            player->ModifyMoney(-ILLUSION_SPECIAL_COST);
                            player->CLOSE_GOSSIP_MENU();
                        }
                        else
                        {
                            player->CastSpell(player, 24710, true);
                            player->ModifyMoney(-ILLUSION_SPECIAL_COST);
                            player->CLOSE_GOSSIP_MENU();
                        }

                    }
                    else
                    {
                        creature->MonsterWhisper("You don't have enough money to receive an illusion", player->GetGUID());
                        player->CLOSE_GOSSIP_MENU();
                    }
                    break;

                //Skeleton Option 100 Gold
                case GOSSIP_ACTION_INFO_DEF+17:
                    if (IsShapeshifted(player))
                    {
                        creature->MonsterWhisper("You can't do this while shapeshifted.", player->GetGUID());
                        player->CLOSE_GOSSIP_MENU();
                    }
                    if (player->HasEnoughMoney(ILLUSION_SPECIAL_COST))
                    {
                        player->CastSpell(player, 24723, true);
                        player->ModifyMoney(-ILLUSION_SPECIAL_COST);
                        player->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        creature->MonsterWhisper("You don't have enough money to receive an illusion", player->GetGUID());
                        player->CLOSE_GOSSIP_MENU();
                    }
                    break;

                //Ghost Costume 100 gold
                case GOSSIP_ACTION_INFO_DEF+18:
                    if (IsShapeshifted(player))
                    {
                        creature->MonsterWhisper("You can't do this while shapeshifted.", player->GetGUID());
                        player->CLOSE_GOSSIP_MENU();
                    }
                    if (player->HasEnoughMoney(ILLUSION_SPECIAL_COST))
                    {
                        if (player->getGender() == GENDER_MALE)
                        {
                            player->CastSpell(player, 24735, true);
                            player->ModifyMoney(-ILLUSION_SPECIAL_COST);
                            player->CLOSE_GOSSIP_MENU();
                        }
                        else
                        {
                            player->CastSpell(player, 24736, true);
                            player->ModifyMoney(-ILLUSION_SPECIAL_COST);
                            player->CLOSE_GOSSIP_MENU();
                        }
                    }
                    else
                    {
                        creature->MonsterWhisper("You don't have enough money to receive an illusion", player->GetGUID());
                        player->CLOSE_GOSSIP_MENU();
                    }
                    break;
                    
                default:
                    break;
            }
            return true;
        }
};

void AddSC_npc_misc_gossips()
{
    new npc_mini_pet_gossip();
    new npc_level_master_gossip();
    new npc_card_master_gossip();
    new npc_raid_master_gossip();
    new npc_illusionist_gossip();
}