#ifndef GLADIATORS_TURN_H
#define GLADIATORS_TURN_H
#include "Gladiator.h"
#include "GladiatorZone.h"


class Turn {
public:
    Turn(int number, const Gladiator &attacker, int damage, GladiatorZone attackZone, GladiatorZone blockZone);

    int getNumber() const;
    Gladiator getAttacker() const;
    GladiatorZone getAttackZone() const;
    GladiatorZone getBlockZone() const;
    int getDamage() const;

private:
    int m_number;
    Gladiator m_attacker;
    int m_damage;
    GladiatorZone m_attackZone;
    GladiatorZone m_blockZone;
};


#endif //GLADIATORS_TURN_H