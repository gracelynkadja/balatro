#include "PairJoker.h"

#include "PokerHandType.h"

std::string PairJoker::getName() const {
    return "Pair Joker";
}

std::string PairJoker::getDescription(const ScoreContext& context) const {
    if (context.handType == PokerHandType::Pair) {
        return "Pair detected, +4 mult";
    }
    return "No effect";
}

void PairJoker::onScoreCalculated(ScoreContext& context) {
    if (context.handType == PokerHandType::Pair) {
        context.mult += 4;
    }
}
