#ifndef GLADIATORS_ITEM_H
#define GLADIATORS_ITEM_H

#include <qstring.h>
#include <utility>
#include "ItemType.h"


class Item {
public:
    Item(QString name, ItemType type, quint8 price, qint8 requiredLevel, qint8 damage, qint8 armor, bool isEquipped);

    [[nodiscard]] QString getName() const;
    [[nodiscard]] ItemType getType() const;
    [[nodiscard]] quint8 getPrice() const;
    [[nodiscard]] qint8 getRequiredLevel() const;
    [[nodiscard]] qint8 getDamage() const;
    [[nodiscard]] qint8 getArmor() const;
    [[nodiscard]] bool isEquipped() const;

private:
    QString m_name;
    ItemType m_type;
    quint8 m_price;
    qint8 m_requiredLevel;
    qint8 m_damage;
    qint8 m_armor;
    bool m_isEquipped;
};


#endif //GLADIATORS_ITEM_H