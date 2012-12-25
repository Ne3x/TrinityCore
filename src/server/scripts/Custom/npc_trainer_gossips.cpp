#include "ScriptPCH.h"

#define MAX_SKILL_LEVEL 450

class npc_profession_trainer_gossip : public CreatureScript
{
    public:
        npc_profession_trainer_gossip(): CreatureScript("npc_profession_trainer_gossip"){}

        bool OnGossipHello(Player* pPlayer, Creature* pCreature)
        {
            if (pPlayer->isInCombat())
            {
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->MonsterWhisper("You are in combat!", pPlayer->GetGUID());
                return true;
            }
            else
            {
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, GOSSIP_TEXT_TRAIN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Advance My Professions" , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
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
                    pPlayer->GetSession()->SendTrainerList(pCreature->GetGUID());
                break;

                case GOSSIP_ACTION_INFO_DEF+1:
                    pPlayer->GetSession()->SendListInventory(pCreature->GetGUID());
                break;

                case GOSSIP_ACTION_INFO_DEF+2://Advance Professions
                    pPlayer->CLOSE_GOSSIP_MENU();
                    //Alchemy
                    if (pPlayer->GetPureMaxSkillValue(SKILL_ALCHEMY) && pPlayer->GetSkillValue(SKILL_ALCHEMY) <= MAX_SKILL_LEVEL)
                    {
                        pPlayer->SetSkill(SKILL_ALCHEMY, 0, MAX_SKILL_LEVEL, MAX_SKILL_LEVEL);
                        pCreature->MonsterWhisper("Alchemy has been advanced.", pPlayer->GetGUID());
                    }
                    //Blacksmith
                    if (pPlayer->GetPureMaxSkillValue(SKILL_BLACKSMITHING) && pPlayer->GetSkillValue(SKILL_BLACKSMITHING) <= MAX_SKILL_LEVEL)
                    {
                        pPlayer->SetSkill(SKILL_BLACKSMITHING, 0, MAX_SKILL_LEVEL, MAX_SKILL_LEVEL);
                        pCreature->MonsterWhisper("Blacksmithing has been advanced.", pPlayer->GetGUID());
                    }
                    //Enchanting
                    if (pPlayer->GetPureMaxSkillValue(SKILL_ENCHANTING) && pPlayer->GetSkillValue(SKILL_ENCHANTING) <= MAX_SKILL_LEVEL)
                    {
                        pPlayer->SetSkill(SKILL_ENCHANTING, 0, MAX_SKILL_LEVEL, MAX_SKILL_LEVEL);
                        pCreature->MonsterWhisper("Enchanting has been advanced.", pPlayer->GetGUID());
                    }
                    //Engineering
                    if (pPlayer->GetPureMaxSkillValue(SKILL_ENGINEERING) && pPlayer->GetSkillValue(SKILL_ENGINEERING) <= MAX_SKILL_LEVEL)
                    {
                        pPlayer->SetSkill(SKILL_ENGINEERING, 0, MAX_SKILL_LEVEL, MAX_SKILL_LEVEL);
                        pCreature->MonsterWhisper("Engineering has been advanced.", pPlayer->GetGUID());
                    }
                    //Inscription
                    if (pPlayer->GetPureMaxSkillValue(SKILL_INSCRIPTION) && pPlayer->GetSkillValue(SKILL_INSCRIPTION) <= MAX_SKILL_LEVEL)
                    {
                        pPlayer->SetSkill(SKILL_INSCRIPTION, 0, MAX_SKILL_LEVEL, MAX_SKILL_LEVEL);
                        pCreature->MonsterWhisper("Inscription has been advanced.", pPlayer->GetGUID());
                    }
                    //Jewelcrafting
                    if (pPlayer->GetPureMaxSkillValue(SKILL_JEWELCRAFTING) && pPlayer->GetSkillValue(SKILL_JEWELCRAFTING) <= MAX_SKILL_LEVEL)
                    {
                        pPlayer->SetSkill(SKILL_JEWELCRAFTING, 0, MAX_SKILL_LEVEL, MAX_SKILL_LEVEL);
                        pCreature->MonsterWhisper("Jewelcrafting has been advanced.", pPlayer->GetGUID());
                    }
                    //Leatherworking
                    if (pPlayer->GetPureMaxSkillValue(SKILL_LEATHERWORKING) && pPlayer->GetSkillValue(SKILL_LEATHERWORKING) <= MAX_SKILL_LEVEL)
                    {
                        pPlayer->SetSkill(SKILL_LEATHERWORKING, 0, MAX_SKILL_LEVEL, MAX_SKILL_LEVEL);
                        pCreature->MonsterWhisper("Leatherworking has been advanced.", pPlayer->GetGUID());
                    }
                    //Tailoring
                    if (pPlayer->GetPureMaxSkillValue(SKILL_TAILORING) && pPlayer->GetSkillValue(SKILL_TAILORING) <= MAX_SKILL_LEVEL)
                    {
                        pPlayer->SetSkill(SKILL_TAILORING, 0, MAX_SKILL_LEVEL, MAX_SKILL_LEVEL);
                        pCreature->MonsterWhisper("Tailoring has been advanced.", pPlayer->GetGUID());
                    }
                    //Herbalism
                    if (pPlayer->GetPureMaxSkillValue(SKILL_HERBALISM) && pPlayer->GetSkillValue(SKILL_HERBALISM) <= MAX_SKILL_LEVEL)
                    {
                        pPlayer->SetSkill(SKILL_HERBALISM, 0, MAX_SKILL_LEVEL, MAX_SKILL_LEVEL);
                        pCreature->MonsterWhisper("Herbalism has been advanced.", pPlayer->GetGUID());
                    }
                    //Mining
                    if (pPlayer->GetPureMaxSkillValue(SKILL_MINING) && pPlayer->GetSkillValue(SKILL_MINING) <= MAX_SKILL_LEVEL)
                    {
                        pPlayer->SetSkill(SKILL_MINING, 0, MAX_SKILL_LEVEL, MAX_SKILL_LEVEL);
                        pCreature->MonsterWhisper("Mining has been advanced.", pPlayer->GetGUID());
                    }
                    //Skinning
                    if (pPlayer->GetPureMaxSkillValue(SKILL_SKINNING) && pPlayer->GetSkillValue(SKILL_SKINNING) <= MAX_SKILL_LEVEL)
                    {
                        pPlayer->SetSkill(SKILL_SKINNING, 0, MAX_SKILL_LEVEL, MAX_SKILL_LEVEL);
                        pCreature->MonsterWhisper("Mining has been advanced.", pPlayer->GetGUID());
                    }
                break;

                default:
                break;
            }
            return true;
        }
};

enum Mounts
{
    //Horde Category
    ORC_MOUNTS          = 1,
    TROLL_MOUNTS        = 2,
    TAUREN_MOUNTS       = 3,
    UNDEAD_MOUNTS       = 4,
    BLOOD_ELF_MOUNTS    = 5,
    //Alliance Category
    HUMAN_MOUNTS        = 6,
    DWARF_MOUNTS        = 7,
    GNOME_MOUNTS        = 8,
    DRAENEI_MOUNTS      = 9,
    NIGHT_ELF_MOUNTS    = 10,
};

class npc_riding_trainer_gossip : public CreatureScript
{
    public:
        npc_riding_trainer_gossip(): CreatureScript("npc_riding_trainer_gossip"){}

        bool OnGossipHello(Player* pPlayer, Creature* pCreature)
        {
            if (pPlayer->isInCombat())
            {
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->MonsterWhisper("You are in combat!", pPlayer->GetGUID());
                return true;
            }
            else
            {

                pPlayer->PrepareQuestMenu(pCreature->GetGUID());
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, GOSSIP_TEXT_TRAIN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
                return true;
            }
        }

        bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 uiAction)
        {
            pPlayer->PlayerTalkClass->ClearMenus();

            switch(uiAction)
            {

                case GOSSIP_ACTION_INFO_DEF:
                    pPlayer->GetSession()->SendTrainerList(pCreature->GetGUID());
                    break;

                case GOSSIP_ACTION_INFO_DEF+1:
                    if (pPlayer->GetTeam() == HORDE)
                    {
                        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Orc Mounts", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Troll Mounts", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
                        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Tauren Mounts", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
                        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Undead Mounts", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5);
                        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Blood Elf Mounts", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+6);
                        pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
                    }
                    if (pPlayer->GetTeam() == ALLIANCE)
                    {
                        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Human Mounts", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+7);
                        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Dwarf Mounts", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+8);
                        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Gnome Mounts", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+9);
                        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Draenei Mounts", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+10);
                        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Night Elf Mounts", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+11);
                        pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
                    }
                    break;
       
                case GOSSIP_ACTION_INFO_DEF+2:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), ORC_MOUNTS);
                    break;

                case GOSSIP_ACTION_INFO_DEF+3:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), TROLL_MOUNTS);
                    break;

                case GOSSIP_ACTION_INFO_DEF+4:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), TAUREN_MOUNTS);
                    break;

                case GOSSIP_ACTION_INFO_DEF+5:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), UNDEAD_MOUNTS);
                    break;

                case GOSSIP_ACTION_INFO_DEF+6:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), BLOOD_ELF_MOUNTS);
                    break;

                case GOSSIP_ACTION_INFO_DEF+7:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), HUMAN_MOUNTS);
                    break;

                case GOSSIP_ACTION_INFO_DEF+8:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), DWARF_MOUNTS);
                    break;

                case GOSSIP_ACTION_INFO_DEF+9:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), GNOME_MOUNTS);
                    break;

                case GOSSIP_ACTION_INFO_DEF+10:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), DRAENEI_MOUNTS);
                    break;

                case GOSSIP_ACTION_INFO_DEF+11:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), NIGHT_ELF_MOUNTS);
                    break;

                default:
                break;
            }
            return true;
        }
};


class npc_dk_trainer_gossip : public CreatureScript
{
    public:
        npc_dk_trainer_gossip(): CreatureScript("npc_dk_trainer_gossip"){}

        bool OnGossipHello(Player* pPlayer, Creature* pCreature)
        {
            if (pPlayer->isInCombat())
            {
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->MonsterWhisper("You are in combat!", pPlayer->GetGUID());
                return true;
            }
            if (pPlayer->getClass() != CLASS_DEATH_KNIGHT)
            {
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->MonsterWhisper("You must be a Death Knight in order to speak to me!", pPlayer->GetGUID());
                return true;
            }
            else
            {
                pPlayer->PrepareQuestMenu(pCreature->GetGUID());
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, GOSSIP_TEXT_TRAIN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
                return true;
            }
        }

        bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 uiAction)
        {
            pPlayer->PlayerTalkClass->ClearMenus();

            switch(uiAction)
            {
                case GOSSIP_ACTION_INFO_DEF:
                    pPlayer->GetSession()->SendTrainerList(pCreature->GetGUID());
                break;
       
                case GOSSIP_ACTION_INFO_DEF+1:
                    pPlayer->GetSession()->SendListInventory(pCreature->GetGUID());
                break;

                default:
                break;
            }
            return true;
        }
};

class npc_class_trainer_gossip : public CreatureScript
{
    public:
        npc_class_trainer_gossip(): CreatureScript("npc_class_trainer_gossip"){}

        bool OnGossipHello(Player* player, Creature* creature)
        {
            if (player->isInCombat())
            {
                player->CLOSE_GOSSIP_MENU();
                creature->MonsterWhisper("You are in combat!", player->GetGUID());
                return true;
            }
            else
            {
                if (creature->isTrainer())
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, GOSSIP_TEXT_TRAIN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRAIN);

                 if (creature->isCanTrainingAndResetTalentsOf(player))
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "I wish to unlearn my talents", GOSSIP_SENDER_MAIN, GOSSIP_OPTION_UNLEARNTALENTS);

                if (player->GetSpecsCount() == 1 && creature->isCanTrainingAndResetTalentsOf(player) && player->getLevel() >= sWorld->getIntConfig(CONFIG_MIN_DUALSPEC_LEVEL))
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "Purchase a Dual Talent Specialization.", GOSSIP_SENDER_MAIN, GOSSIP_OPTION_LEARNDUALSPEC);

                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
                return true;
            }
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 uiAction)
        {
            player->PlayerTalkClass->ClearMenus();

            switch (uiAction)
            {
                case GOSSIP_ACTION_TRAIN:
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

                case GOSSIP_OPTION_UNLEARNTALENTS:
                    player->CLOSE_GOSSIP_MENU();
                    player->SendTalentWipeConfirm(creature->GetGUID());
                break;

                case GOSSIP_OPTION_LEARNDUALSPEC:
                    if (player->GetSpecsCount() == 1 && !(player->getLevel() < sWorld->getIntConfig(CONFIG_MIN_DUALSPEC_LEVEL)))
                    {   
                        if (!player->HasEnoughMoney(10000000))
                        {
                            player->SendBuyError(BUY_ERR_NOT_ENOUGHT_MONEY, 0, 0, 0);
                            player->PlayerTalkClass->SendCloseGossip();
                            break;
                        }
                        else
                        {
                            player->ModifyMoney(-10000000);

                            // Cast spells that teach dual spec
                            // Both are also ImplicitTarget self and must be cast by player
                            player->CastSpell(player, 63680, true, NULL, NULL, player->GetGUID());
                            player->CastSpell(player, 63624, true, NULL, NULL, player->GetGUID());

                            // Should show another Gossip text with "Congratulations..."
                            player->PlayerTalkClass->SendCloseGossip();
                        }
                    }
                break;
            }
            return true;
        }
};

void AddSC_npc_trainer_gossips()
{
    new npc_profession_trainer_gossip();
    new npc_riding_trainer_gossip();
    new npc_dk_trainer_gossip();
    new npc_class_trainer_gossip();
}