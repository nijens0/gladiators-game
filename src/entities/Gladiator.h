#ifndef GLADIATORS_GLADIATOR_H
#define GLADIATORS_GLADIATOR_H
#include <qstring.h>
#include <qlist.h>
#include "Item.h"


class Gladiator {
public:
    explicit Gladiator(QString name, int level = 0, int experience = 0,
                       int hp = 100, int maxHp = 100, int gold = 5, int freePoints = 3,
                       int strength = 5, int agility = 5, int intuition = 5,
                       int endurance = 5, bool isBot = false);

    [[nodiscard]] QString getName() const;
    [[nodiscard]] int getLevel() const;
    [[nodiscard]] int getExperience() const;
    [[nodiscard]] int getHp() const;
    [[nodiscard]] int getMaxHp() const;
    [[nodiscard]] int getGold() const;
    [[nodiscard]] int getFreePoints() const;
    [[nodiscard]] int getStrength() const;
    [[nodiscard]] int getAgility() const;
    [[nodiscard]] int getIntuition() const;
    [[nodiscard]] int getEndurance() const;
    [[nodiscard]] bool isBot() const;
    [[nodiscard]] QList<Item> getInventory() const;
    [[nodiscard]] bool isAlive() const;
    [[nodiscard]] int getDamage() const;
    [[nodiscard]] int getArmor() const;

private:
    QString m_name;
    int m_level;
    int m_experience;
    int m_hp;
    int m_maxHp;
    int m_gold;
    int m_freePoints;
    int m_strength;
    int m_agility;
    int m_intuition;
    int m_endurance;
    bool m_isBot;
    QList<Item> m_inventory;
};


#endif //GLADIATORS_GLADIATOR_H
