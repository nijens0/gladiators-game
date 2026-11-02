#include "InventoryService.h"

void InventoryService::equip(Gladiator gladiator, const Item &item) {
    gladiator.addItem(item);
}

void InventoryService::unequip(Gladiator gladiator, const Item &item) {
    gladiator.removeItem(item);
}