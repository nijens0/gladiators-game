#ifndef GLADIATORS_BATTLESERVICE_H
#define GLADIATORS_BATTLESERVICE_H

#include "../entities/Turn.h"
#include "../entities/Fight.h"


class BattleService {
public:
    BattleService() = delete;

    static int calculateDamage(Gladiator &attacker, const Gladiator &defender,
                               const Turn &attackersTurn, const Turn &defendersTurn);
    static Turn makeTurn(const Gladiator &attacker, GladiatorZone attack, GladiatorZone block);
    static Turn makeBotTurn(const Gladiator &bot);
    static bool chanceProcs(const std::function<float()> &getChance);
    static void finishFight(Fight& fight);
};


#endif //GLADIATORS_BATTLESERVICE_H
