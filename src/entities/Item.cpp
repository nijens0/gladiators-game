#include "Item.h"

Item::Item(QString name, const ItemType type, const quint8 price, const qint8 requiredLevel,
         const qint8 damage, const qint8 armor, const bool isEquipped)
        : m_name(std::move(name)), m_type(type), m_price(price),
          m_requiredLevel(requiredLevel), m_damage(damage),
          m_armor(armor), m_isEquipped(isEquipped) {}

QString Item::getName() const {
    return m_name;
}

ItemType Item::getType() const {
    return m_type;
}

quint8 Item::getPrice() const {
    return m_price;
}

qint8 Item::getRequiredLevel() const {
    return m_requiredLevel;
}

qint8 Item::getDamage() const {
    return m_damage;
}

qint8 Item::getArmor() const {
    return m_armor;
}

bool Item::isEquipped() const {
    return m_isEquipped;
}