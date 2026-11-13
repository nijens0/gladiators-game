#ifndef GLADIATORS_FIGHT_H
#define GLADIATORS_FIGHT_H

#include "FightType.h"
#include "Gladiator.h"
#include "qdatetime.h"
#include "Turn.h"

class Fight {
public:
    explicit Fight(FightType type = FightType::BOT);

    [[nodiscard]] FightType getType() const;
    [[nodiscard]] bool isFinished() const;
    void addParticipant(Gladiator* participant);
    [[nodiscard]] QList<Gladiator*> getParticipants() const;
    [[nodiscard]] std::optional<Gladiator*> getWinner();
    [[nodiscard]] QList<Turn> getTurns() const;

private:
    FightType m_type;
    bool m_isFinished;
    QList<Gladiator*> m_participants;
    QList<Turn> m_turns;
};


#endif //GLADIATORS_FIGHT_H
