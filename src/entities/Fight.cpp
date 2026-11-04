#include "Fight.h"

Fight::Fight(QPair<Gladiator, Gladiator> participants, const bool isFinished,
             QDateTime startedAt,const FightType type)
    : m_type(type), m_isFinished(isFinished),
      m_participants(participants) {
}

FightType Fight::getType() const {
    return m_type;
}

bool Fight::isFinished() const {
    return m_isFinished;
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