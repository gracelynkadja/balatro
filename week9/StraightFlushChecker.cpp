#include "StraightFlushChecker.h"

#include "FlushChecker.h"
#include "StraightChecker.h"

bool StraightFlushChecker::checkPokerHand(const std::vector<Card>& cards) const {
    if (cards.size() != 5) {
        return false;
    }

    StraightChecker straightChecker;
    FlushChecker flushChecker;
    return straightChecker.checkPokerHand(cards) && flushChecker.checkPokerHand(cards);
}

PokerHandType StraightFlushChecker::getHandType() const {
    return PokerHandType::StraightFlush;
}
