#ifndef GLADIATORS_SHOPSERVICE_H
#define GLADIATORS_SHOPSERVICE_H

#include "../entities/Gladiator.h"

class ShopService {
public:
    ShopService() = delete;

    static bool buy(Gladiator& gladiator, const Item& item);

    static QList<Item> getItems();

private:
    static const QList<Item> m_items;
};


#endif //GLADIATORS_SHOPSERVICE_H