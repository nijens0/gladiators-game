#ifndef GLADIATORS_GLADIATOR_H
#define GLADIATORS_GLADIATOR_H
#include <qstring.h>
#include <qlist.h>

#include "Item.h"

class Gladiator {
public:
    explicit Gladiator(QString name, int level = 1, int experience = 0,
                       int gold = 5, int freePoints = 3,
                       int strength = 1, int agility = 1, int intuition = 1,
                       int endurance = 1, bool isBot = false);

    [[nodiscard]] QString getName() const;
    [[nodiscard]] int getLevel() const;
    [[nodiscard]] int getExperience() const;
    void addExperience(int amount);
    [[nodiscard]] int getHp() const;
    [[nodiscard]] int getMaxHp() const;
    [[nodiscard]] int getGold() const;
    void addGold(int gold);
    void subGold(int gold);
    [[nodiscard]] int getFreePoints() const;
    void addFreePoints();
    void subFreePoint();
    [[nodiscard]] int getStrength() const;
    void addStrength();
    [[nodiscard]] int getAgility() const;
    void addAgility();
    [[nodiscard]] int getIntuition() const;
    void addIntuition();
    [[nodiscard]] int getEndurance() const;
    void addEndurance();
    [[nodiscard]] bool isBot() const;
    [[nodiscard]] QList<Item> getInventory() const;
    void addItem(const Item& item);
    void removeItem(const Item& item);
    [[nodiscard]] bool isAlive() const;
    [[nodiscard]] int getDamage() const;
    [[nodiscard]] int getArmor() const;

private:
    QString m_name;
    int m_level;
    int m_experience;
    int m_hp;
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
