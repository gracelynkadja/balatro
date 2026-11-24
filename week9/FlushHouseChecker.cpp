#include "FlushHouseChecker.h"

#include "FlushChecker.h"
#include "FullHouseChecker.h"

bool FlushHouseChecker::checkPokerHand(const std::vector<Card>& cards) const {
    if (cards.size() != 5) {
        return false;
    }

    FullHouseChecker fullHouseChecker;
    FlushChecker flushChecker;
    return fullHouseChecker.checkPokerHand(cards) && flushChecker.checkPokerHand(cards);
}

PokerHandType FlushHouseChecker::getHandType() const {
    return PokerHandType::FlushHouse;
}
