#include "TwoPairChecker.h"

#include "PokerUtils.h"

bool TwoPairChecker::checkPokerHand(const std::vector<Card>& cards) const {
    if (cards.size() != 5) {
        return false;
    }

    return countPairs(countRanks(cards)) == 2;
}

PokerHandType TwoPairChecker::getHandType() const {
    return PokerHandType::TwoPair;
}
