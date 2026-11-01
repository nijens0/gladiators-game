#include "Fight.h"

Fight::Fight(QPair<Gladiator, Gladiator> participants,
             const int id, const int turnNumber, const bool isFinished,
             QDateTime startedAt,const FightType type)
    : m_id(id), m_type(type), m_turnNumber(turnNumber), m_isFinished(isFinished),
      m_startedAt(std::move(startedAt)), m_participants(participants) {
}

int Fight::getId() const {
    return m_id;
}

FightType Fight::getType() const {
    return m_type;
}

int Fight::getTurnNumber() const {
    return m_turnNumber;
}

bool Fight::isFinished() const {
    return m_isFinished;
}

QDateTime Fight::getStartedAt() const {
    return m_startedAt;
}

QPair<Gladiator, Gladiator> Fight::getParticipants() const {
    return m_participants;
}

std::optional<Gladiator> Fight::getWinner() const {
    auto [first, second] = getParticipants();

    if (!first.isAlive()) return second;
    if (!second.isAlive()) return first;

    return std::nullopt;
}

QList<Turn> Fight::getTurns() const {
    return m_turns;
}