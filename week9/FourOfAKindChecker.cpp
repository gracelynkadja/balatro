#include "FourOfAKindChecker.h"

#include "PokerUtils.h"

bool FourOfAKindChecker::checkPokerHand(const std::vector<Card>& cards) const {
    if (cards.size() != 5) {
        return false;
    }

    return hasNOfAKind(countRanks(cards), 4);
}

PokerHandType FourOfAKindChecker::getHandType() const {
    return PokerHandType::FourOfAKind;
}
