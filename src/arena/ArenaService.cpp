#include "ArenaService.h"
#include "../shop/ShopService.h"

namespace {
    Gladiator makeBot(const QString& name, const int level,
                      const int strength, const int agility,
                      const int intuition, const int endurance,
                      const QList<ItemId>& items) {
        Gladiator gladiator(name, level, 0, 0, 0,
                            strength, agility, intuition, endurance, true);
        for (const ItemId id : items) {
            gladiator.addItem(ShopService::findItem(id));
        }
        return gladiator;
    }

    Gladiator makeMixSlovesniy() {
        return makeBot("Мих Словесный", 1, 0, 1, 1, 10, {});
    }

    Gladiator makeMaximus() {
        return makeBot("Максимус", 2, 3, 2, 2, 3, {
            ItemId::Stick, ItemId::LeatherJacket
        });
    }

    Gladiator makeAurelius() {
        return makeBot("Аврелий", 3, 3, 1, 1, 8, {
            ItemId::Stick, ItemId::LeatherJacket, ItemId::Pot, ItemId::SchoolBackpack
        });
    }

    Gladiator makeAugustine() {
        return makeBot("Августин", 4, 3, 9, 2, 2, {
            ItemId::SharpStick, ItemId::LeatherJacket, ItemId::Hat
        });
    }

    Gladiator makeMarcus() {
        return makeBot("Марк", 5, 4, 2, 10, 3, {
            ItemId::SharpStick, ItemId::ChainMail, ItemId::Pot
        });
    }

    Gladiator makeCicero() {
        return makeBot("Цицерон", 6, 14, 3, 3, 2, {
            ItemId::IronDagger, ItemId::TShirt
        });
    }

    Gladiator makeCaesar() {
        return makeBot("Цезарь", 7, 7, 6, 6, 6, {
            ItemId::IronDagger, ItemId::Brigandine, ItemId::ChainHelmet, ItemId::Buckler
        });
    }

    Gladiator makeCornelius() {
        return makeBot("Корнелий", 8, 5, 2, 2, 19, {
            ItemId::IronDagger, ItemId::Brigandine, ItemId::ChainHelmet, ItemId::KnightShield
        });
    }

    Gladiator makePompey() {
        return makeBot("Помпей", 9, 14, 3, 4, 10, {
            ItemId::Rapier, ItemId::Brigandine, ItemId::ChainHelmet, ItemId::TowerShield
        });
    }

    Gladiator makeQuma() {
        return makeBot("quma", 10, 10, 15, 15, 1, {
            ItemId::KnightLance, ItemId::PlateArmor, ItemId::KnightHelmet, ItemId::Buckler
        });
    }
}

ArenaService::ArenaService() {
    m_gladiators = {
        makeMixSlovesniy(),
        makeMaximus(),
        makeAurelius(),
        makeAugustine(),
        makeMarcus(),
        makeCicero(),
        makeCaesar(),
        makeCornelius(),
        makePompey(),
        makeQuma()
    };

    for (auto& bot : m_gladiators) {
        Fight fight;
        fight.addParticipant(&bot);
        m_fights.append(fight);
    }
}

void ArenaService::joinFight(Fight fight, Gladiator gladiator) {
    fight.addParticipant(&gladiator);
}