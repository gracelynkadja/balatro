#include "FlushFiveChecker.h"

#include "FiveOfAKindChecker.h"
#include "FlushChecker.h"

bool FlushFiveChecker::checkPokerHand(const std::vector<Card>& cards) const {
    if (cards.size() != 5) {
        return false;
    }

    FiveOfAKindChecker fiveOfAKindChecker;
    FlushChecker flushChecker;
    return fiveOfAKindChecker.checkPokerHand(cards) && flushChecker.checkPokerHand(cards);
}

PokerHandType FlushFiveChecker::getHandType() const {
    return PokerHandType::FlushFive;
}
