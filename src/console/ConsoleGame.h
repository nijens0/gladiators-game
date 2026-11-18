#ifndef GLADIATORS_CONSOLEGAME_H
#define GLADIATORS_CONSOLEGAME_H

#include "../arena/ArenaService.h"
#include "../entities/Gladiator.h"

class ConsoleGame {
public:
    ConsoleGame();

    int run();

private:
    bool loadOrCreatePlayer();
    void save();
    void showStatus();
    void fight();
    void shop();
    void shopCategory(ItemType type);
    void inventory();
    void stats();

    ArenaService m_arena;
    Gladiator m_player;
    int m_defeatedCount;
};


#endif //GLADIATORS_CONSOLEGAME_H
