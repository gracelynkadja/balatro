#include "FullHouseChecker.h"

#include "PokerUtils.h"

bool FullHouseChecker::checkPokerHand(const std::vector<Card>& cards) const {
    if (cards.size() != 5) {
        return false;
    }

    const auto rankCount = countRanks(cards);
    return hasNOfAKind(rankCount, 3) && hasNOfAKind(rankCount, 2);
}

PokerHandType FullHouseChecker::getHandType() const {
    return PokerHandType::FullHouse;
}
