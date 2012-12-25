#include "Transmogrification.h"
#include "Player.h"

//Checks if the item can be used for transmogrification
bool Transmogrification::ValidItemForTransmogrification(Item* item)
{
    //Make sure that the item still exist.
    if (item)
    {
        uint32 itemType = item->GetTemplate()->Class;

        if (itemType == ITEM_CLASS_WEAPON || itemType == ITEM_CLASS_ARMOR)
        {
            if (item->GetTemplate()->SubClass != ITEM_SUBCLASS_WEAPON_FISHING_POLE)
            {
                //If you want to allow other type of items to be transmogrified then set appropriate qualities to true
                switch (item->GetTemplate()->Quality)
                {
                    case ITEM_QUALITY_POOR      : return false;                   
                    case ITEM_QUALITY_NORMAL    : return true;
                    case ITEM_QUALITY_UNCOMMON  : return true;
                    case ITEM_QUALITY_RARE      : return true;
                    case ITEM_QUALITY_EPIC      : return true;
                    case ITEM_QUALITY_LEGENDARY : return true;
                    case ITEM_QUALITY_ARTIFACT  : return false;
                    case ITEM_QUALITY_HEIRLOOM  : return true;
                    default                     : return false;
                }
            }
        }
    }
    return false;
}

//Validation for transmogrification
TransmogrificationErrors Transmogrification::ValidateTransmogrification(Player* player, Item* item, Item* transItem)
{
    if (!ValidItemForTransmogrification(item) || !ValidItemForTransmogrification(transItem))
        return TRANSMOG_ERR_INVALID_ITEMS;

    if (!item->IsEquipped())
        return TRANSMOG_ERR_ITEM_NOT_EQUIPPED;

    if (transItem->IsInBag())
        return TRANSMOG_ERR_TRANSITEM_NOT_IN_BAG;

    if (transItem->GetTemplate()->DisplayInfoID == item->GetTemplate()->DisplayInfoID)
        return TRANSMOG_ERR_SAME_DISPLAY;

    if (player->CanUseItem(transItem) != EQUIP_ERR_OK)
        return TRANSMOG_ERR_TRANSITEM_UNUSABLE;

    uint32 transItemClass = transItem->GetTemplate()->Class;
    uint32 itemClass = item->GetTemplate()->Class;
    uint32 transItemSubClass = transItem->GetTemplate()->SubClass;
    uint32 itemSubClass = item->GetTemplate()->SubClass;
    uint32 transItemInvType = transItem->GetTemplate()->InventoryType;
    uint32 itemInvType = item->GetTemplate()->InventoryType;

    if (transItemClass != itemClass)
        return TRANSMOG_ERR_ITEMS_HAVE_DIFF_CLASS;

    switch (transItemClass)
    {
        case ITEM_CLASS_WEAPON:

        //Check that items types are equal and allow main and off hand weapons to be transmogrified with one handed weapons
        if (itemInvType == transItemInvType ||
            ((itemInvType == INVTYPE_WEAPONMAINHAND || itemInvType == INVTYPE_WEAPONOFFHAND) && transItemInvType == INVTYPE_WEAPON))

            //Check that items subclasses are equal and allow ranged weapons to be tranmogrified with other ranged subclasses
            if (transItemSubClass == itemSubClass ||
                ((transItemSubClass == ITEM_SUBCLASS_WEAPON_BOW || transItemSubClass == ITEM_SUBCLASS_WEAPON_GUN || transItemSubClass == ITEM_SUBCLASS_WEAPON_CROSSBOW) && 
                  (itemSubClass == ITEM_SUBCLASS_WEAPON_BOW || itemSubClass == ITEM_SUBCLASS_WEAPON_GUN || itemSubClass == ITEM_SUBCLASS_WEAPON_CROSSBOW)))
                   return TRANSMOG_ERR_OK;
        break;

        case ITEM_CLASS_ARMOR:

        //Check that items types are equal and allow ropes to be transmogrified with chest and other way around.
        if (itemInvType == transItemInvType ||
            (itemInvType == INVTYPE_CHEST && transItemInvType == INVTYPE_ROBE) || (itemInvType == INVTYPE_ROBE && transItemInvType == INVTYPE_CHEST))
            if (transItemSubClass == itemSubClass)
                return TRANSMOG_ERR_OK;
        break;

        default: break;
    }

    return TRANSMOG_ERR_VALIDATION_FAILED;
}

void Transmogrification::Transmogrify(Player* player, Item* item, Item* transItem)
{
    if (ValidateTransmogrification(player, item, transItem) == TRANSMOG_ERR_OK)
    {
        transItem->SetNotRefundable(player);
        transItem->SetBinding(true);
        uint32 fakeEntry = transItem->GetEntry();
        item->SetFakeEntry(fakeEntry);
        CharacterDatabase.PExecute("REPLACE INTO transmogrification (guid, fakeEntry) VALUES (%u, %u)", item->GetGUIDLow(), fakeEntry);
        player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID + (item->GetSlot() * 2), fakeEntry);
        player->PlayDirectSound(3337);
        player->GetSession()->SendAreaTriggerMessage("Transmogrification was succesful");
    }
    else                     
        player->GetSession()->SendNotification("An error occured during transmogirification");
}

void Transmogrification::RemoveTransmogrificationAtSlot(Player* player, uint8 slot)
{
    if (Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
    {
        if (item->HasFakeEntry())
        {
            item->DeleteFakeEntry();
            CharacterDatabase.PExecute("DELETE FROM transmogrification WHERE guid = %u", item->GetGUIDLow());
            player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID + (item->GetSlot() * 2), item->GetEntry());
            player->GetSession()->SendAreaTriggerMessage("Transmogrification from the %s slot has been removed", Transmogrification::GetSlotName(slot));
            player->PlayDirectSound(3337);
        }
        else
            player->GetSession()->SendAreaTriggerMessage("No transmogrification was found on the %s slot", Transmogrification::GetSlotName(slot));
    }
}

void Transmogrification::RemoveAllTransmogrification(Player* player)
{
    bool removed = false;
    for (uint8 slot = EQUIPMENT_SLOT_START; slot < EQUIPMENT_SLOT_END; slot++)
    {
        if (Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
        {
            if (item->HasFakeEntry())
            {
                item->DeleteFakeEntry();
                CharacterDatabase.PExecute("DELETE FROM transmogrification WHERE guid = %u", item->GetGUIDLow());
                player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID + (item->GetSlot() * 2), item->GetEntry());
                removed = true;
            }
        }
    }

    if (removed)
    {
        player->GetSession()->SendAreaTriggerMessage("Transmogrifications has been removed from equipped items");
        player->PlayDirectSound(3337);
    }
    else
        player->GetSession()->SendNotification("You have no transmogrifications on the equipped items");
}

char* Transmogrification::GetSlotName(uint8 slot)
{
    switch (slot)
    {
        case EQUIPMENT_SLOT_HEAD      : return "Head";
        case EQUIPMENT_SLOT_SHOULDERS : return "Shoulders";
        case EQUIPMENT_SLOT_CHEST     : return "Chest";
        case EQUIPMENT_SLOT_WAIST     : return "Waist";
        case EQUIPMENT_SLOT_LEGS      : return "Legs";
        case EQUIPMENT_SLOT_FEET      : return "Feet";
        case EQUIPMENT_SLOT_WRISTS    : return "Wrists";
        case EQUIPMENT_SLOT_HANDS     : return "Hands";
        case EQUIPMENT_SLOT_BACK      : return "Back";
        case EQUIPMENT_SLOT_MAINHAND  : return "Main hand";
        case EQUIPMENT_SLOT_OFFHAND   : return "Off hand";
        case EQUIPMENT_SLOT_RANGED    : return "Ranged";
        default                       : return "Invalid";
    }
}