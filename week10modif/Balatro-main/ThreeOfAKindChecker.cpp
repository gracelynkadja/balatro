#include "ThreeOfAKindChecker.h"

#include "PokerUtils.h"

bool ThreeOfAKindChecker::checkPokerHand(const std::vector<Card>& cards) const {
    if (cards.size() != 5) {
        return false;
    }

    const auto rankCount = countRanks(cards);
    return hasNOfAKind(rankCount, 3) && countPairs(rankCount) == 0;
}

PokerHandType ThreeOfAKindChecker::getHandType() const {
    return PokerHandType::ThreeOfAKind;
}
