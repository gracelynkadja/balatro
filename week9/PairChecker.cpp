#include "PairChecker.h"

#include "PokerUtils.h"

bool PairChecker::checkPokerHand(const std::vector<Card>& cards) const {
    if (cards.size() != 5) {
        return false;
    }

    const auto rankCount = countRanks(cards);
    return rankCount.size() == 4 && countPairs(rankCount) == 1;
}

PokerHandType PairChecker::getHandType() const {
    return PokerHandType::Pair;
}
