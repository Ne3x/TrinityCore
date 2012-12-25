#include "ScriptPCH.h"

enum Vendor
{
    //Weapon Category
    VENDOR_1H           = 1,
    VENDOR_2H           = 2,
    VENDOR_RANGED       = 3,
    VENDOR_SHIELDS      = 4,
    //Armor Category
    VENDOR_HELMETS      = 5,
    VENDOR_SHOULDERS    = 6,
    VENDOR_CHESTS       = 7,
    VENDOR_WRISTS       = 8,
    VENDOR_GLOVES       = 9,
    VENDOR_BELTS        = 10,
    VENDOR_PANTS        = 11,
    VENDOR_BOOTS        = 12,
    VENDOR_CLOAKS       = 13,
    VENDOR_TOTEM_SLOT   = 14,
    //Jewelery Category
    VENDOR_NECKS        = 15,
    VENDOR_RINGS        = 16,
    VENDOR_TRINKETS     = 17,
};

enum TierVendor
{
    ROGUE   = 1,
    HUNTER  = 2,
    WARRIOR = 3,
    DRUID   = 4,
    MAGE    = 5,
    WARLOCK = 6,
    PALADIN = 7,
    SHAMAN  = 8,
    PRIEST  = 9
};

class npc_tier3_vendor : public CreatureScript
{
    public:
        npc_tier3_vendor(): CreatureScript("npc_tier3_vendor"){}

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
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Tier III Rogue Set", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Tier III Hunter Set", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Tier III Warrior/Death Knight Set", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Tier III Druid Set", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Tier III Mage Set", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Tier III Warlock Set", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Tier III Paladin Set", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+6);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Tier III Shaman Set", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+7);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Tier III Priest Set", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+8);
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
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), ROGUE);
                    break;

                case GOSSIP_ACTION_INFO_DEF+1:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), HUNTER);
                    break;

                case GOSSIP_ACTION_INFO_DEF+2:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), WARRIOR);
                    break;

                case GOSSIP_ACTION_INFO_DEF+3:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), DRUID);
                    break;

                case GOSSIP_ACTION_INFO_DEF+4:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), MAGE);
                    break;

                case GOSSIP_ACTION_INFO_DEF+5:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), WARLOCK);
                    break;

                case GOSSIP_ACTION_INFO_DEF+6:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), PALADIN);
                    break;

                case GOSSIP_ACTION_INFO_DEF+7:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), SHAMAN);
                    break;

                case GOSSIP_ACTION_INFO_DEF+8:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), PRIEST);
                    break;

                default:
                    break;
            }
            return true;
        }
};

class npc_furious_vendor : public CreatureScript
{
    public:
        npc_furious_vendor(): CreatureScript("npc_furious_vendor"){}

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
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Season VI Weapons", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Season VI Armor Sets", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Season VI Misc Items", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
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
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), 1);
                    break;

                case GOSSIP_ACTION_INFO_DEF+1:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), 2);
                    break;

                case GOSSIP_ACTION_INFO_DEF+2:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), 3);
                    break;

                default:
                break;
            }
            return true;
        }
};

class npc_relentless_vendor : public CreatureScript
{
    public:
        npc_relentless_vendor(): CreatureScript("npc_relentless_vendor"){}

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
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Season VII Weapons", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Season VII Armor Sets", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Season VII Misc Items", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
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
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), 1);
                    break;

                case GOSSIP_ACTION_INFO_DEF+1:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), 2);
                    break;

                case GOSSIP_ACTION_INFO_DEF+2:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), 3);
                    break;

                default:
                break;
            }
            return true;
        }
};

class npc_wrathful_vendor : public CreatureScript
{
    public:
        npc_wrathful_vendor(): CreatureScript("npc_wrathful_vendor"){}

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
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Season VIII Armor Sets", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Season VIII Misc Items", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Season VIII level:264 Weapons", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Season VIII level:277 Weapons", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
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
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), 1);
                    break;

                case GOSSIP_ACTION_INFO_DEF+1:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), 2);
                    break;

                case GOSSIP_ACTION_INFO_DEF+2:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), 3);
                    break;

                case GOSSIP_ACTION_INFO_DEF+3:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), 4);
                    break;

                default:
                    break;
            }
            return true;
        }
};

class npc_ulduar_vendor : public CreatureScript
{
    public:
        npc_ulduar_vendor(): CreatureScript("npc_ulduar_vendor"){}

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
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Ulduar Weapons", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Ulduar Armor", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Ulduar Jewelary", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);              
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
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "One-Handed Weapons", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Two-Handed Weapons", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5);
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Ranged Weapons", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+6);
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Held In Off-Hand", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+7);
                    pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
                    break;

                case GOSSIP_ACTION_INFO_DEF+1:
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Helmets", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+8);
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Shoulders", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+9);
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Chests", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+10);
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Wrists", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+11);
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Gloves", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+12);
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Belts", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+13);
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Pants", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+14);
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Boots", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+15);
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Cloaks", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+16);
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Idols/Totems/Librams", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+17);   
                    pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
                    break;

                case GOSSIP_ACTION_INFO_DEF+2:
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Necks", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+18);
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Rings", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+19);
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Trinkets", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+20);
                    pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
                    break;

                case GOSSIP_ACTION_INFO_DEF+4:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), VENDOR_1H);
                    break;

                case GOSSIP_ACTION_INFO_DEF+5:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), VENDOR_2H);
                    break;

                case GOSSIP_ACTION_INFO_DEF+6:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), VENDOR_RANGED);
                    break;

                case GOSSIP_ACTION_INFO_DEF+7:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), VENDOR_SHIELDS);
                    break;

                case GOSSIP_ACTION_INFO_DEF+8:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), VENDOR_HELMETS);
                    break;

                case GOSSIP_ACTION_INFO_DEF+9:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), VENDOR_SHOULDERS);
                    break;

                case GOSSIP_ACTION_INFO_DEF+10:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), VENDOR_CHESTS);
                    break;

                case GOSSIP_ACTION_INFO_DEF+11:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), VENDOR_WRISTS);
                    break;

                case GOSSIP_ACTION_INFO_DEF+12:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), VENDOR_GLOVES);
                    break;

                case GOSSIP_ACTION_INFO_DEF+13:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), VENDOR_BELTS);
                    break;

                case GOSSIP_ACTION_INFO_DEF+14:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), VENDOR_PANTS);
                    break;

                case GOSSIP_ACTION_INFO_DEF+15:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), VENDOR_BOOTS);
                    break;

                case GOSSIP_ACTION_INFO_DEF+16:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), VENDOR_CLOAKS);
                    break;

                case GOSSIP_ACTION_INFO_DEF+17:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), VENDOR_TOTEM_SLOT);
                    break;

                case GOSSIP_ACTION_INFO_DEF+18:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), VENDOR_NECKS);
                    break;

                case GOSSIP_ACTION_INFO_DEF+19:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), VENDOR_RINGS);
                    break;

                case GOSSIP_ACTION_INFO_DEF+20:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), VENDOR_TRINKETS);
                    break;

                default:
                break;
            }
            return true;
        }
};

class npc_icecrown_vendor : public CreatureScript
{
    public:
        npc_icecrown_vendor(): CreatureScript("npc_icecrown_vendor"){}

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
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Tier X Armor Sets", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Tier X Misc Items", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
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
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), 1);
                    break;

                case GOSSIP_ACTION_INFO_DEF+1:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), 2);
                    break;

                default:
                    break;
            }
            return true;
        }
};

class npc_glyph_vendor : public CreatureScript
{
    public:
        npc_glyph_vendor(): CreatureScript("npc_glyph_vendor"){}

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
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Death Knight Glyphs", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Druid Glyphs", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Hunter Glyphs", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Mage Glyphs", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Paladin Glyphs", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Priest Glyphs", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5);
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
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), 1);
                    break;

                case GOSSIP_ACTION_INFO_DEF+1:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), 2);
                    break;

                case GOSSIP_ACTION_INFO_DEF+2:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), 3);
                    break;

                case GOSSIP_ACTION_INFO_DEF+3:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), 4);
                    break;

                case GOSSIP_ACTION_INFO_DEF+4:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), 5);
                    break;

                case GOSSIP_ACTION_INFO_DEF+5:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), 6);
                    break;

                default:
                    break;
            }
            return true;
        }
};

class npc_glyph_vendor_2 : public CreatureScript
{
    public:
        npc_glyph_vendor_2(): CreatureScript("npc_glyph_vendor_2"){}

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
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Rogue Glyphs", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Shaman Glyphs", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Warlock Glyphs", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Warrior Glyphs", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
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
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), 1);
                    break;

                case GOSSIP_ACTION_INFO_DEF+1:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), 2);
                    break;

                case GOSSIP_ACTION_INFO_DEF+2:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), 3);
                    break;

                case GOSSIP_ACTION_INFO_DEF+3:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), 4);
                    break;

                default:
                    break;
            }
            return true;
        }
};

class npc_gem_vendor : public CreatureScript
{
    public:
        npc_gem_vendor(): CreatureScript("npc_gem_vendor"){}

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
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Meta and Prismatic Gems", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Red Gems", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Blue Gems", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Yellow Gems", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Purple Gems", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Green Gems", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Orange Gems", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+6);
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
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), 1);
                    break;

                case GOSSIP_ACTION_INFO_DEF+1:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), 2);
                    break;

                case GOSSIP_ACTION_INFO_DEF+2:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), 3);
                    break;

                case GOSSIP_ACTION_INFO_DEF+3:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), 4);
                    break;

                case GOSSIP_ACTION_INFO_DEF+4:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), 5);
                    break;

                case GOSSIP_ACTION_INFO_DEF+5:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), 6);
                    break;

                case GOSSIP_ACTION_INFO_DEF+6:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), 7);
                    break;

                default:
                    break;
            }
            return true;
        }
};

class npc_enchanting_vendor : public CreatureScript
{
    public:
        npc_enchanting_vendor(): CreatureScript("npc_enchanting_vendor"){}

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
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Weapon Enchants", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Chest and Gloves Enchants", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Wrists, Boots and Back Enchants", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Other Enchants", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
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
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), 1);
                    break;

                case GOSSIP_ACTION_INFO_DEF+1:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), 2);
                    break;

                case GOSSIP_ACTION_INFO_DEF+2:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), 3);
                    break;

                case GOSSIP_ACTION_INFO_DEF+3:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), 4);
                    break;

                default:
                    break;
            }
            return true;
        }
};

class npc_heirloom_vendor : public CreatureScript
{
    public:
        npc_heirloom_vendor(): CreatureScript("npc_heirloom_vendor"){}

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
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Heirloom Weapons", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Heirloom Armor", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Heirloom Jewelary", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
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
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), 1);
                    break;

                case GOSSIP_ACTION_INFO_DEF+1:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), 2);
                    break;

                case GOSSIP_ACTION_INFO_DEF+2:
                    pPlayer->SEND_VENDORLIST_ADVANCED(pCreature->GetGUID(), 3);
                    break;

                default:
                    break;
            }
            return true;
        }
};

class npc_glory_vendor : public CreatureScript
{
    public:
        npc_glory_vendor(): CreatureScript("npc_glory_vendor"){}

        bool OnGossipHello(Player* pPlayer, Creature* pCreature)
        {
            if (pPlayer->isInCombat())
            {
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->MonsterWhisper("You are in combat!", pPlayer->GetGUID());
                return true;
            }
            if (pPlayer->GetGlory() < 1000000)
            {
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->MonsterWhisper("You need to reach Glory Rank 14 in order to use my services!", pPlayer->GetGUID());
                return true;
            }
            else
            {
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Vendor", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
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
                    pPlayer->GetSession()->SendListInventory(pCreature->GetGUID());
                break;

                default:
                break;
            }
            return true;
        }
};

void AddSC_npc_vendor_gossips()
{
    new npc_tier3_vendor();
    new npc_furious_vendor();
    new npc_relentless_vendor();
    new npc_wrathful_vendor();
    new npc_ulduar_vendor();
    new npc_icecrown_vendor();
    new npc_glyph_vendor();
    new npc_glyph_vendor_2();
    new npc_gem_vendor();
    new npc_enchanting_vendor();
    new npc_heirloom_vendor();
    new npc_glory_vendor();
}