#include "StraightChecker.h"

#include <algorithm>
#include <vector>

bool StraightChecker::checkPokerHand(const std::vector<Card>& cards) const {
    if (cards.size() != 5) {
        return false;
    }

    std::vector<int> ranks;
    ranks.reserve(cards.size());

    for (const Card& card : cards) {
        ranks.push_back(card.getRankValue());
    }

    std::sort(ranks.begin(), ranks.end());
    if (std::adjacent_find(ranks.begin(), ranks.end()) != ranks.end()) {
        return false;
    }

    const std::vector<int> aceLowStraight = {2, 3, 4, 5, 14};
    if (ranks == aceLowStraight) {
        return true;
    }

    for (std::size_t i = 1; i < ranks.size(); ++i) {
        if (ranks[i] != ranks[i - 1] + 1) {
            return false;
        }
    }

    return true;
}

PokerHandType StraightChecker::getHandType() const {
    return PokerHandType::Straight;
}
