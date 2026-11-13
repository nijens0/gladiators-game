#include "Gladiator.h"
#include <cmath>

constexpr int BASE_HP = 100;
constexpr float HP_AND_DAMAGE_MULTIPLIER = 1.05f;
constexpr float DODGE_AND_CRIT_MULTIPLIER = 1.0167f;
constexpr int ADDITIONAL_STATS = 3;

Gladiator::Gladiator(QString name, const int level, const int experience,
                     const int gold, const int freePoints,
                     const int strength, const int agility, const int intuition,
                     const int endurance, const bool isBot) :
                m_name(std::move(name)), m_level(level), m_experience(experience),
                m_gold(gold), m_freePoints(freePoints),m_strength(strength),
                m_agility(agility), m_intuition(intuition), m_endurance(endurance), m_isBot(isBot) {
    m_hp = getMaxHp();
}

QString Gladiator::getName() const {
    return m_name;
}

int Gladiator::getLevel() const {
    return m_level;
}

void Gladiator::addLevel() {
    m_level++;
}

int Gladiator::getExperience() const {
    return m_experience;
}

void Gladiator::addExperience(const int amount) {
    m_experience += amount;
}

int Gladiator::getHp() const {
    return m_hp;
}

void Gladiator::setMaxHp() {
    m_hp = getMaxHp();
}

void Gladiator::subHp(const int amount) {
    m_hp -= amount;
}

int Gladiator::getMaxHp() const {
    return BASE_HP * (std::pow(HP_AND_DAMAGE_MULTIPLIER, m_endurance));
}

int Gladiator::getGold() const {
    return m_gold;
}

void Gladiator::addGold(const int gold) {
    m_gold += gold;
}

void Gladiator::subGold(const int gold) {
    if (gold > m_gold) return;

    m_gold -= gold;
}

int Gladiator::getFreePoints() const {
    return m_freePoints;
}

void Gladiator::addFreePoints() {
    m_freePoints += ADDITIONAL_STATS;
}

void Gladiator::subFreePoint() {
    if (m_freePoints <= 0) return;
    m_freePoints--;
}

int Gladiator::getDamage() {
    auto damage = 0;
    for (const Item &item : m_inventory) {
        if (item.isEquipped()) {
            damage += item.getDamage();
        }
    }
    return damage * (std::pow(HP_AND_DAMAGE_MULTIPLIER, m_strength));
}

float Gladiator::getCritChance() const {
    return std::round((std::pow(DODGE_AND_CRIT_MULTIPLIER, m_intuition) - 1) * 100) / 100;
}

float Gladiator::getDodgeChance() const {
    return std::round((std::pow(DODGE_AND_CRIT_MULTIPLIER, m_agility) - 1) * 100) / 100;
}

int Gladiator::getStrength() const {
    return m_strength;
}

void Gladiator::addStrength() {
    m_strength++;
}

int Gladiator::getAgility() const {
    return m_agility;
}

void Gladiator::addAgility() {
    m_agility++;
}

int Gladiator::getIntuition() const {
    return m_intuition;
}

void Gladiator::addIntuition() {
    m_intuition++;
}

int Gladiator::getEndurance() const {
    return m_endurance;
}

void Gladiator::addEndurance() {
    m_endurance++;
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
        if (item.isEquipped() && item.getType() != ItemType::SHIELD) {
            armor += item.getArmor();
        }
    }

    return armor;
}

int Gladiator::getShieldArmor() const {
    auto armor = 0;

    for (const Item &item : m_inventory) {
        if (item.isEquipped() && item.getType() == ItemType::SHIELD) {
            armor = item.getArmor();
        }
    }

    return armor;
}