#include "Fight.h"

Fight::Fight(const FightType type)
    : m_type(type) {
    m_isFinished = false;
}

FightType Fight::getType() const {
    return m_type;
}

bool Fight::isFinished() const {
    return m_isFinished;
}

void Fight::addParticipant(Gladiator* participant) {
    if (m_participants.length() >= 2) {
        throw std::runtime_error("В бою не может быть больше 2 гладиаторов!");
    }
    m_participants.append(participant);
}

QList<Gladiator*> Fight::getParticipants() const {
    return m_participants;
}

std::optional<Gladiator*> Fight::getWinner() const {
    if (m_participants.length() < 2) return std::nullopt;

    auto first = m_participants.first();
    auto second = m_participants.last();

    if (!first->isAlive()) return second;
    if (!second->isAlive()) return first;

    return std::nullopt;
}

QList<Turn> Fight::getTurns() const {
    return m_turns;
}