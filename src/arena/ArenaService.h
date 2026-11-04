#ifndef GLADIATORS_ARENASERVICE_H
#define GLADIATORS_ARENASERVICE_H

#include "../entities/Fight.h"

class ArenaService {
public:
    ArenaService();

    void joinFight(Fight fight, Gladiator gladiator);
    void start(Fight fight);

    QList<Gladiator> getGladiators();
    QList<Fight> getFights();

private:
    QList<Gladiator> m_gladiators;
    QList<Fight> m_fights;
};


#endif //GLADIATORS_ARENASERVICE_H