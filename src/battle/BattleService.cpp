#include "BattleService.h"
#include <QRandomGenerator>

namespace {

}

Turn BattleService::makeTurn(const Gladiator &attacker, const GladiatorZone attack, const GladiatorZone block) {
    return {attacker, attack, block};
}

Turn BattleService::makeBotTurn(const Gladiator &bot) {
    auto attackZone = static_cast<GladiatorZone>(QRandomGenerator::global()->bounded(
        static_cast<int>(GladiatorZone::COUNT)));
    auto blockZone = static_cast<GladiatorZone>(QRandomGenerator::global()->bounded(
        static_cast<int>(GladiatorZone::COUNT)));

    return {bot, attackZone, blockZone};
}

int BattleService::calculateDamage(Gladiator &attacker, const Gladiator &defender,
                                   const Turn &attackersTurn, const Turn &defendersTurn) {

    int attackersDamage = attacker.getDamage();
    const int attackersArmor = attacker.getArmor();


    const int defendersDamage = defender.getDamage();
    const int defendersArmor = defender.getArmor();
    const int defendersShield = defender.getShieldArmor();

    if (attackersTurn.getAttackZone() == defendersTurn.getBlockZone()) {
        attackersDamage = std::max(0, attackersDamage - defendersShield);
    }

    const bool isCrit = chanceProcs([&attacker] { return attacker.getCritChance(); });
    const bool isDodge = chanceProcs([&defender] { return defender.getDodgeChance(); });

    if (isCrit && !isDodge) return attackersDamage;
    if (isDodge) {
        attacker.subHp(std::max(0, (defendersDamage - attackersArmor) / 2));
        return 0;
    }
    return std::max(0, attackersDamage - defendersArmor);
}

bool BattleService::chanceProcs(const std::function<float()> &getChance) {
    const float chance = getChance();
    const float roll = static_cast<float>(QRandomGenerator::global()->generateDouble());

    return chance > roll;
}

void BattleService::finishFight(Fight& fight) {
    const auto winner = fight.resolveWinner();
    if (!winner) return;

    auto* gladiator = *winner;
    if (gladiator->isBot()) return;

    const auto level = gladiator->getLevel();

    gladiator->addFreePoints();
    gladiator->addLevel();
    gladiator->addGold(level * 10);
    gladiator->addExperience(1000);
}