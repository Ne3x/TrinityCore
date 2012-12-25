#include "ScriptPCH.h"

class item_arena_stone : public ItemScript
{
    public:
        item_arena_stone() : ItemScript("item_arena_stone") {}

        bool OnUse(Player* player, Item* item, SpellCastTargets const &targets)
        {
            if (player->isInCombat() || player->isInFlight() || player->isDead() || player->IsMounted())
            {
                player->SendEquipError(EQUIP_ERR_NOT_IN_COMBAT, item, NULL);
                return true;
            }

            else
            {
                player->ModifyArenaPoints(+100);
                player->DestroyItemCount(item->GetEntry(), 1, true);
                return true;
            }
        }
};

void AddSC_item_arena_stone()
{
    new item_arena_stone();
}