#ifndef GLADIATORS_INVENTORYSERVICE_H
#define GLADIATORS_INVENTORYSERVICE_H

#include "../entities/Gladiator.h"

class InventoryService {
public:
    InventoryService() = delete;

    static void equip(Gladiator gladiator, const Item &item);
    static void unequip(Gladiator gladiator, const Item &item);
};


#endif //GLADIATORS_INVENTORYSERVICE_H