#include "Gladiator.h"

Gladiator::Gladiator(QString name, const int level, const int experience,
                     const int hp, const int maxHp, const int gold, const int freePoints,
                     const int strength, const int agility, const int intuition,
                     const int endurance, const bool isBot) :
                m_name(std::move(name)), m_level(level), m_experience(experience),
                m_hp(hp), m_maxHp(maxHp), m_gold(gold), m_freePoints(freePoints),
                m_strength(strength), m_agility(agility), m_intuition(intuition),
                m_endurance(endurance), m_isBot(isBot) {}

QString Gladiator::getName() const {
    return m_name;
}

int Gladiator::getLevel() const {
    return m_level;
}

int Gladiator::getExperience() const {
    return m_experience;
}

int Gladiator::getHp() const {
    return m_hp;
}

int Gladiator::getMaxHp() const {
    return m_maxHp;
}

int Gladiator::getGold() const {
    return m_gold;
}

int Gladiator::getFreePoints() const {
    return m_freePoints;
}

int Gladiator::getStrength() const {
    return m_strength;
}

int Gladiator::getAgility() const {
    return m_agility;
}

int Gladiator::getIntuition() const {
    return m_intuition;
}

int Gladiator::getEndurance() const {
    return m_endurance;
}

bool Gladiator::isBot() const {
    return m_isBot;
}

QList<Item> Gladiator::getInventory() const {
    return m_inventory;
}

void Gladiator::addItem(const Item& item) {
    m_inventory.append(item);
}

void Gladiator::removeItem(const Item& item) {

    for (int i = 0; i < m_inventory.length(); i++) {
        if (m_inventory[i] == item) {
            m_inventory.removeAt(i);
            return;
        }
    }
}

bool Gladiator::isAlive() const {
    return m_hp >= 0;
}

int Gladiator::getDamage() const {
    auto damage = 0;

    for (const Item &item : m_inventory) {
        if (item.isEquipped()) {
            damage += item.getDamage();
        }
    }

    return damage;
}

int Gladiator::getArmor() const {
    auto armor = 0;

    for (const Item &item : m_inventory) {
        if (item.isEquipped()) {
            armor += item.getArmor();
        }
    }

    return armor;
}