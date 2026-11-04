#ifndef GLADIATORS_FIGHT_H
#define GLADIATORS_FIGHT_H

#include "FightType.h"
#include "Gladiator.h"
#include "qdatetime.h"
#include "Turn.h"

class Fight {
public:
    explicit Fight(QPair<Gladiator, Gladiator> participants,
                   bool isFinished = false, QDateTime startedAt = QDateTime::currentDateTime(),
                   FightType type = FightType::BOT);

    [[nodiscard]] FightType getType() const;
    [[nodiscard]] bool isFinished() const;
    [[nodiscard]] QDateTime getStartedAt() const;
    [[nodiscard]] QPair<Gladiator, Gladiator> getParticipants() const;
    [[nodiscard]] std::optional<Gladiator> getWinner() const;
    [[nodiscard]] QList<Turn> getTurns() const;

private:
    FightType m_type;
    bool m_isFinished;
    QDateTime m_startedAt;
    QPair<Gladiator, Gladiator> m_participants;
    QList<Turn> m_turns;
};


#endif //GLADIATORS_FIGHT_H
