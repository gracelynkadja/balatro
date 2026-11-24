#include "RoyalFlushChecker.h"

#include "FlushChecker.h"

#include <algorithm>
#include <vector>

bool RoyalFlushChecker::checkPokerHand(const std::vector<Card>& cards) const {
    if (cards.size() != 5) {
        return false;
    }

    FlushChecker flushChecker;
    if (!flushChecker.checkPokerHand(cards)) {
        return false;
    }

    std::vector<int> ranks;
    ranks.reserve(cards.size());

    for (const Card& card : cards) {
        ranks.push_back(card.getRankValue());
    }

    std::sort(ranks.begin(), ranks.end());
    return ranks == std::vector<int>{10, 11, 12, 13, 14};
}

PokerHandType RoyalFlushChecker::getHandType() const {
    return PokerHandType::RoyalFlush;
}
