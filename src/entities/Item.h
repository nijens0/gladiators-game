#ifndef GLADIATORS_ITEM_H
#define GLADIATORS_ITEM_H

#include <qstring.h>
#include <utility>
#include "ItemType.h"


class Item {
public:
    Item(QString name, ItemType type, int price, int requiredLevel, int damage, int armor, bool isEquipped);

    [[nodiscard]] QString getName() const;
    [[nodiscard]] ItemType getType() const;
    [[nodiscard]] int getPrice() const;
    [[nodiscard]] int getRequiredLevel() const;
    [[nodiscard]] int getDamage() const;
    [[nodiscard]] int getArmor() const;
    [[nodiscard]] bool isEquipped() const;

private:
    QString m_name;
    ItemType m_type;
    int m_price;
    int m_requiredLevel;
    int m_damage;
    int m_armor;
    bool m_isEquipped;
};


#endif //GLADIATORS_ITEM_H