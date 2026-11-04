#ifndef GLADIATORS_ITEM_H
#define GLADIATORS_ITEM_H

#include <qstring.h>
#include "ItemName.h"
#include "ItemType.h"


class Item {
public:
    Item(ItemId id, ItemType type, int price, int requiredLevel, int damage, int armor, bool isEquipped);

    bool operator==(const Item&) const = default;

    [[nodiscard]] ItemId getId() const;
    [[nodiscard]] QString getName() const;
    [[nodiscard]] ItemType getType() const;
    [[nodiscard]] int getPrice() const;
    [[nodiscard]] int getRequiredLevel() const;
    [[nodiscard]] int getDamage() const;
    [[nodiscard]] int getArmor() const;
    [[nodiscard]] bool isEquipped() const;

private:
    ItemId m_id;
    ItemType m_type;
    int m_price;
    int m_requiredLevel;
    int m_damage;
    int m_armor;
    bool m_isEquipped;
};


#endif //GLADIATORS_ITEM_H