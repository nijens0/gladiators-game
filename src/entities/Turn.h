#ifndef GLADIATORS_TURN_H
#define GLADIATORS_TURN_H
#include "Gladiator.h"
#include "GladiatorZone.h"


class Turn {
public:
    Turn(const Gladiator &attacker, GladiatorZone attackZone, GladiatorZone blockZone);

    Gladiator getAttacker() const;
    GladiatorZone getAttackZone() const;
    GladiatorZone getBlockZone() const;
    int getDamage() const;

private:
    Gladiator m_attacker;
    GladiatorZone m_attackZone;
    GladiatorZone m_blockZone;
};


#endif //GLADIATORS_TURN_H