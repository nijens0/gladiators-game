#include "CharacterService.h"

bool CharacterService::addStatPoint(Gladiator &gladiator, const StatType stat) {
    if (gladiator.getFreePoints() == 0) return false;

    switch (stat) {
        case StatType::Strength: gladiator.addStrength();
            break;
        case StatType::Agility: gladiator.addAgility();
            break;
        case StatType::Endurance: gladiator.addEndurance();
            break;
        case StatType::Intuition: gladiator.addIntuition();
    }

    gladiator.subFreePoint();
    return true;
}

void CharacterService::gainExperience(Gladiator& gladiator, const int amount) {
    gladiator.addExperience(amount);
}
