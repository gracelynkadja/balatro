#include "FiveOfAKindChecker.h"

#include "PokerUtils.h"

bool FiveOfAKindChecker::checkPokerHand(const std::vector<Card>& cards) const {
    if (cards.size() != 5) {
        return false;
    }

    return hasNOfAKind(countRanks(cards), 5);
}

PokerHandType FiveOfAKindChecker::getHandType() const {
    return PokerHandType::FiveOfAKind;
}
