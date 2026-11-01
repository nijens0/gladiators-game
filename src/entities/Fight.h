#ifndef GLADIATORS_FIGHT_H
#define GLADIATORS_FIGHT_H

#include "FightType.h"
#include "Gladiator.h"
#include "qdatetime.h"

class Fight {
public:
    Fight(QPair<Gladiator, Gladiator> participants, int id, int turnNumber,
          bool isFinished = false, QDateTime startedAt = QDateTime::currentDateTime(),
          FightType type = FightType::BOT);

    [[nodiscard]] int getId() const;
    [[nodiscard]] FightType getType() const;
    [[nodiscard]] int getTurnNumber() const;
    [[nodiscard]] bool isFinished() const;
    [[nodiscard]] QDateTime getStartedAt() const;
    [[nodiscard]] QPair<Gladiator, Gladiator> getParticipants() const;
    [[nodiscard]] std::optional<Gladiator> getWinner() const;

private:
    int m_id;
    FightType m_type;
    int m_turnNumber;
    bool m_isFinished;
    QDateTime m_startedAt;
    QPair<Gladiator, Gladiator> m_participants;
};


#endif //GLADIATORS_FIGHT_H
