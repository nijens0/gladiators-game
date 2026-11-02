#ifndef GLADIATORS_CHARACTERSERVICE_H
#define GLADIATORS_CHARACTERSERVICE_H

#include "StatType.h"
#include "../entities/Gladiator.h"

class CharacterService {
public:
    CharacterService() = delete;

    static bool addStatPoint(Gladiator& gladiator, StatType stat);
    static void gainExperience(Gladiator& gladiator, int amount);
};


#endif //GLADIATORS_CHARACTERSERVICE_H
