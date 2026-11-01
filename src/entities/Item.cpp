#include "Item.h"

Item::Item(QString name, const ItemType type, const int price, const int requiredLevel,
         const int damage, const int armor, const bool isEquipped)
        : m_name(std::move(name)), m_type(type), m_price(price),
          m_requiredLevel(requiredLevel), m_damage(damage),
          m_armor(armor), m_isEquipped(isEquipped) {}

QString Item::getName() const {
    return m_name;
}

ItemType Item::getType() const {
    return m_type;
}

int Item::getPrice() const {
    return m_price;
}

int Item::getRequiredLevel() const {
    return m_requiredLevel;
}

int Item::getDamage() const {
    return m_damage;
}

int Item::getArmor() const {
    return m_armor;
}

bool Item::isEquipped() const {
    return m_isEquipped;
}