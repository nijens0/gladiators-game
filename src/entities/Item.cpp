#include "Item.h"

Item::Item(const ItemId id, const ItemType type, const int price, const int requiredLevel,
           const int damage, const int armor, const bool isEquipped)
    : m_id(id), m_type(type), m_price(price),
      m_requiredLevel(requiredLevel), m_damage(damage),
      m_armor(armor), m_isEquipped(isEquipped) {
}

ItemId Item::getId() const {
    return m_id;
}

QString Item::getName() const {
    switch (m_id) {
        case ItemId::Slipper: return {"Тапок"};
        case ItemId::Stick: return {"Палка"};
        case ItemId::SharpStick: return {"Заострённая Палка"};
        case ItemId::IronDagger: return {"Железный Кинжал"};
        case ItemId::Rapier: return {"Рапира"};
        case ItemId::KnightLance: return {"Рыцарское копье"};
        case ItemId::TShirt: return {"Майка"};
        case ItemId::LeatherJacket: return {"Кожаная Куртка"};
        case ItemId::ChainMail: return {"Кольчуга"};
        case ItemId::Brigandine: return {"Бригантина"};
        case ItemId::PlateArmor: return {"Латный Доспех"};
        case ItemId::Hat: return {"Шапка"};
        case ItemId::Pot: return {"Кастрюля"};
        case ItemId::HardHat: return {"Строительная Каска"};
        case ItemId::ChainHelmet: return {"Кольчужный шлем"};
        case ItemId::KnightHelmet: return {"Закртый Рыцарский Шлем"};
        case ItemId::Cardboard: return {"Лист Картона"};
        case ItemId::SchoolBackpack: return {"Школьный Рюкзак"};
        case ItemId::Buckler: return {"Баклер"};
        case ItemId::KnightShield: return {"Круглый Рыцарский Щит"};
        case ItemId::TowerShield: return {"Ростовой Щит"};
    }
    return {};
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
