#ifndef TRANSMOGRIFICATION_H
#define TRANSMOGRIFICATION_H

enum TransmogrificationErrors
{
    TRANSMOG_ERR_OK                         = 0,
    TRANSMOG_ERR_ITEMS_NOT_IN_WORLD         = 1,
    TRANSMOG_ERR_ITEM_NOT_EQUIPPED          = 2,
    TRANSMOG_ERR_TRANSITEM_NOT_IN_BAG       = 3,
    TRANSMOG_ERR_SAME_DISPLAY               = 4,
    TRANSMOG_ERR_TRANSITEM_UNUSABLE         = 5,
    TRANSMOG_ERR_ITEMS_HAVE_DIFF_CLASS      = 6,
    TRANSMOG_ERR_INVALID_ITEMS              = 7,
    TRANSMOG_ERR_VALIDATION_FAILED          = 8
};

class Transmogrification
{
    public:
        static bool ValidItemForTransmogrification(Item* item);
        static TransmogrificationErrors ValidateTransmogrification(Player* player, Item* item, Item* transItem);
        static void Transmogrify(Player* player, Item* item, Item* transItem);
        static void RemoveTransmogrificationAtSlot(Player* player, uint8 slot);
        static void RemoveAllTransmogrification(Player* player);
        static char* GetSlotName(uint8 slot);
};
#endif