#include "ScriptPCH.h"
#include "Transmogrification.h"

//Configuration
enum configuration
{
    TRANS_PRICE_MULTIPLIER = 2 //Controls by how much price should be multipled.
};

class npc_transmogrifier_gossip : public CreatureScript
{
    public:
        npc_transmogrifier_gossip() : CreatureScript("npc_transmogrifier_gossip") { }

        bool OnGossipHello (Player* player, Creature* creature)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Transmogrify", GOSSIP_ACTION_INFO_DEF, 0);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Remove Transmogrification", GOSSIP_ACTION_INFO_DEF+3, 0);
            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());    
            return true;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
        {
            player->PlayerTalkClass->ClearMenus();

            switch (sender)
            {
                case GOSSIP_ACTION_INFO_DEF:
                    GenerateEquipedItems(player);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Back..", GOSSIP_ACTION_INFO_DEF+6, 0);
                    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                    break;

                case GOSSIP_ACTION_INFO_DEF+1:
                    GenerateTransmogrificationItems(player, creature, action);                       
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Back..", GOSSIP_ACTION_INFO_DEF+6, 0);
                    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                    break;

                case GOSSIP_ACTION_INFO_DEF+2:
                    player->ModifyMoney(-1*GetTransmogrificationPrice(_item));
                    Transmogrification::Transmogrify(player, _item, Items[action]);
                    player->CLOSE_GOSSIP_MENU();
                    break;

                case GOSSIP_ACTION_INFO_DEF+3:
                    GenerateItemsWithTransmogrification(player);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_INTERACT_1, "Remove all transmogrifications", GOSSIP_ACTION_INFO_DEF+5, 0, "Remove transmogrifications from all equipped items?", 0, false);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Back..", GOSSIP_ACTION_INFO_DEF+6, 0);
                    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                    break;

               case GOSSIP_ACTION_INFO_DEF+4:
                    Transmogrification::RemoveTransmogrificationAtSlot(player, action);
                    OnGossipHello(player, creature);
                    break;

                case GOSSIP_ACTION_INFO_DEF+5:
                    Transmogrification::RemoveAllTransmogrification(player);
                    OnGossipHello(player, creature);
                    break;

                case GOSSIP_ACTION_INFO_DEF+6:
                    OnGossipHello(player, creature);
                    break;

                default: break;
            }
            return true;
        }

    private:
        std::map<uint64, Item*> Items; // Items[item guid] = item reference 

        Item* _item; //Reference to the item that will be used for transmogrification

        //Custom: price will be based of the sell price of item that is being transmogrified * multiplied in the config enum
        uint32 GetTransmogrificationPrice(Item* item)
        {
            return (item->GetTemplate()->SellPrice * TRANS_PRICE_MULTIPLIER);
        }

        //This method will generate all possible equipment that can be used for transmogrification
        void GenerateEquipedItems(Player* player)
        {
            int allowedSlots[12] = {EQUIPMENT_SLOT_HEAD, EQUIPMENT_SLOT_SHOULDERS, EQUIPMENT_SLOT_CHEST, EQUIPMENT_SLOT_WAIST, EQUIPMENT_SLOT_LEGS, EQUIPMENT_SLOT_FEET, 
                                    EQUIPMENT_SLOT_WRISTS, EQUIPMENT_SLOT_HANDS,EQUIPMENT_SLOT_BACK, EQUIPMENT_SLOT_MAINHAND, EQUIPMENT_SLOT_OFFHAND, EQUIPMENT_SLOT_RANGED};

            for (uint8 i = EQUIPMENT_SLOT_START; i < 12; i++)
            {
                if (Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, allowedSlots[i]))
                {
                    if (Transmogrification::ValidItemForTransmogrification(item))
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, Transmogrification::GetSlotName(allowedSlots[i]), GOSSIP_ACTION_INFO_DEF+1, allowedSlots[i]);
                }
            }
        }

        void GenerateTransmogrificationItems(Player* player, Creature* creature, uint32 slot)
        {
            bool result = false;
            if (Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
            {
                Items.clear();
                _item = item;

                for (uint8 i = INVENTORY_SLOT_ITEM_START; i < INVENTORY_SLOT_ITEM_END; i++)
                {  
                    if (Item* transItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
                    {
                        if (Transmogrification::ValidateTransmogrification(player, item, transItem) == TRANSMOG_ERR_OK)
                        {
                            result = true;
                            uint32 transItemGUIDLow = transItem->GetGUIDLow();
                            Items[transItemGUIDLow] = transItem;
                            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_INTERACT_1, transItem->GetTemplate()->Name1, GOSSIP_ACTION_INFO_DEF+2, transItemGUIDLow, "Using this item for transmogrify will bind it to you and make it non-refundable and non-tradeable.\nDo you wish to continue?\n\n"+ item->GetTemplate()->Name1, GetTransmogrificationPrice(item), false);
                        }
  
                    }
                }
            }

            if (!result)
                player->GetSession()->SendNotification("No appropriate items were found in the backpack that could be used for transmogrification");
        }

        void GenerateItemsWithTransmogrification(Player* player)
        {
            int allowedSlots[12] = {EQUIPMENT_SLOT_HEAD, EQUIPMENT_SLOT_SHOULDERS, EQUIPMENT_SLOT_CHEST, EQUIPMENT_SLOT_WAIST, EQUIPMENT_SLOT_LEGS, EQUIPMENT_SLOT_FEET, 
                                    EQUIPMENT_SLOT_WRISTS, EQUIPMENT_SLOT_HANDS,EQUIPMENT_SLOT_BACK, EQUIPMENT_SLOT_MAINHAND, EQUIPMENT_SLOT_OFFHAND, EQUIPMENT_SLOT_RANGED};

            for (uint8 i = EQUIPMENT_SLOT_START; i < 12; i++)
            {
                if (Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, allowedSlots[i]))
                {
                    if (item->HasFakeEntry())
                        player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_INTERACT_1, (std::string)Transmogrification::GetSlotName(allowedSlots[i]) + " slot", GOSSIP_ACTION_INFO_DEF+4, allowedSlots[i], "Remove transmogrification from "+(std::string)Transmogrification::GetSlotName(allowedSlots[i])+" slot?", 0, false);
                }
            }
        }
};

void AddSC_npc_transmogrifier_gossip()
{
    new npc_transmogrifier_gossip();
}




 