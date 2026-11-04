#ifndef GLADIATORS_SAVESERVICE_H
#define GLADIATORS_SAVESERVICE_H

#include <optional>
#include "../entities/Gladiator.h"


class SaveService {
public:
    SaveService() = delete;

    static bool savePlayer(const Gladiator& player);
    static std::optional<Gladiator> loadPlayer();

    static bool saveProgress(int defeatedCount);
    static int loadProgress();
};


#endif //GLADIATORS_SAVESERVICE_H