#include "Turn.h"

Turn::Turn(const int number, const Gladiator &attacker, const int damage,
           const GladiatorZone attackZone, const GladiatorZone blockZone)
    : m_number(number), m_attacker(attacker), m_damage(damage),
      m_attackZone(attackZone), m_blockZone(blockZone) {}

int Turn::getNumber() const {
    return m_number;
}

Gladiator Turn::getAttacker() const {
    return m_attacker;
}

int Turn::getDamage() const {
    return m_damage;
}

GladiatorZone Turn::getBlockZone() const {
    return m_blockZone;
}

GladiatorZone Turn::getAttackZone() const {
    return m_attackZone;
}
