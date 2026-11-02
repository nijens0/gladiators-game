#include "ShopService.h"

const QList<Item> ShopService::m_items = {
    Item{QString("Тапок"), ItemType::WEAPON, 5, 1, 1, 0, false},
    Item{QString("Палка"), ItemType::WEAPON, 10, 2, 10, 0, false},
    Item{QString("Заострённая Палка"), ItemType::WEAPON, 15, 4, 20, 0, false},
    Item{QString("Железный Кинжал"), ItemType::WEAPON, 20, 6, 30, 0, false},
    Item{QString("Рапира"), ItemType::WEAPON, 25, 8, 40, 0, false},
    Item{QString("Рыцарское Копье"), ItemType::WEAPON, 35, 9, 40, 7, false},

    Item{QString("Майка"), ItemType::ARMOR, 5, 1, 0, 1, false},
    Item{QString("Кожаная Куртка"), ItemType::ARMOR, 10, 2, 0, 6, false},
    Item{QString("Кольчуга"), ItemType::ARMOR, 15, 5, 0, 12, false},
    Item{QString("Бригантина"), ItemType::ARMOR, 20, 7, 0, 18, false},
    Item{QString("Латный Доспех"), ItemType::ARMOR, 40, 10, 0, 24, false},

    Item{QString("Шапка"), ItemType::HELMET, 5, 1, 0, 1, false},
    Item{QString("Кастрюля"), ItemType::HELMET, 7, 3, 0, 3, false},
    Item{QString("Строительная Каска"), ItemType::HELMET, 9, 6, 0, 6, false},
    Item{QString("Кольчужный Шлем"), ItemType::HELMET, 12, 7, 0, 9, false},
    Item{QString("Закрытый Рыцарский Шлем"), ItemType::HELMET, 15, 10, 0, 12, false},

    Item{QString("Лист Картона"), ItemType::SHIELD, 5, 1, 0, 1, false},
    Item{QString("Школьный Рюкзак"), ItemType::SHIELD, 10, 3, 0, 10, false},
    Item{QString("Баклер"), ItemType::SHIELD, 15, 4, 0, 20, false},
    Item{QString("Круглый Рыцарский Щит"), ItemType::SHIELD, 20, 8, 0, 30, false},
    Item{QString("Ростовой щит"), ItemType::SHIELD, 25, 9, 0, 40, false},
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