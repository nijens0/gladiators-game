#ifndef GLADIATORS_ARENASERVICE_H
#define GLADIATORS_ARENASERVICE_H

#include "../entities/Fight.h"

class ArenaService {
public:
    ArenaService();

    Fight createFight(FightType type, Gladiator creator);

    QList<Gladiator> getGladiators();

private:
    QList<Gladiator> m_gladiators;
};


#endif //GLADIATORS_ARENASERVICE_H