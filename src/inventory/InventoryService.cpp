#include "InventoryService.h"

void InventoryService::equip(Gladiator& gladiator, const Item &item) {
    if (item.isEquipped()) return;

    for (const Item& owned : gladiator.getInventory()) {
        if (owned.isEquipped() && owned.getType() == item.getType()) {
            gladiator.setItemEquipped(owned, false);
        }
    }

    gladiator.setItemEquipped(item, true);
}

void InventoryService::unequip(Gladiator& gladiator, const Item &item) {
    gladiator.setItemEquipped(item, false);
}
