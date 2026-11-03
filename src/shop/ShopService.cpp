#include "ShopService.h"

const QList<Item> ShopService::m_items = {
    Item{ItemId::Slipper, ItemType::WEAPON, 5, 1, 1, 0, false},
    Item{ItemId::Stick, ItemType::WEAPON, 10, 2, 10, 0, false},
    Item{ItemId::SharpStick, ItemType::WEAPON, 15, 4, 20, 0, false},
    Item{ItemId::IronDagger, ItemType::WEAPON, 20, 6, 30, 0, false},
    Item{ItemId::Rapier, ItemType::WEAPON, 25, 8, 40, 0, false},
    Item{ItemId::KnightLance, ItemType::WEAPON, 35, 9, 40, 7, false},

    Item{ItemId::TShirt, ItemType::ARMOR, 5, 1, 0, 1, false},
    Item{ItemId::LeatherJacket, ItemType::ARMOR, 10, 2, 0, 6, false},
    Item{ItemId::ChainMail, ItemType::ARMOR, 15, 5, 0, 12, false},
    Item{ItemId::Brigandine, ItemType::ARMOR, 20, 7, 0, 18, false},
    Item{ItemId::PlateArmor, ItemType::ARMOR, 40, 10, 0, 24, false},

    Item{ItemId::Hat, ItemType::HELMET, 5, 1, 0, 1, false},
    Item{ItemId::Pot, ItemType::HELMET, 7, 3, 0, 3, false},
    Item{ItemId::HardHat, ItemType::HELMET, 9, 6, 0, 6, false},
    Item{ItemId::ChainHelmet, ItemType::HELMET, 12, 7, 0, 9, false},
    Item{ItemId::KnightHelmet, ItemType::HELMET, 15, 10, 0, 12, false},

    Item{ItemId::Cardboard, ItemType::SHIELD, 5, 1, 0, 1, false},
    Item{ItemId::SchoolBackpack, ItemType::SHIELD, 10, 3, 0, 10, false},
    Item{ItemId::Buckler, ItemType::SHIELD, 15, 4, 0, 20, false},
    Item{ItemId::KnightShield, ItemType::SHIELD, 20, 8, 0, 30, false},
    Item{ItemId::TowerShield, ItemType::SHIELD, 25, 9, 0, 40, false},
};

bool ShopService::buy(Gladiator& gladiator, const Item& item) {
    const auto gold = gladiator.getGold();
    const auto price = item.getPrice();

    if (price > gold) {
        return false;
    }

    gladiator.subGold(price);
    return true;
}

QList<Item> ShopService::getItems() {
    return m_items;
}