#include "FlushChecker.h"

#include "PokerUtils.h"

bool FlushChecker::checkPokerHand(const std::vector<Card>& cards) const {
    if (cards.size() != 5) {
        return false;
    }

    const auto suitCount = countSuits(cards);
    for (const auto& entry : suitCount) {
        if (entry.second == 5) {
            return true;
        }
    }

    return false;
}

PokerHandType FlushChecker::getHandType() const {
    return PokerHandType::Flush;
}
