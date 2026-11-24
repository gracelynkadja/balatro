#include "HandChecker.h"
#include <algorithm>
#include <map>
#include <set>
#include <vector>

HandType HandChecker::check(const ChosenHand& chosen) const {
    const std::vector<Card> cards = chosen.getCards();
    const int countCards = static_cast<int>(cards.size());
    if (countCards == 0) return HandType::HighCard;

    std::map<int, int> rankCounts;
    for (const Card& card : cards) ++rankCounts[card.rank];

    std::vector<int> groups;
    for (const auto& entry : rankCounts) groups.push_back(entry.second);
    std::sort(groups.rbegin(), groups.rend());

    // As in Week 8, Straight and Flush require exactly five selected cards.
    bool flush = countCards == 5;
    for (const Card& card : cards)
        if (card.suit != cards.front().suit) flush = false;

    bool straight = false;
    if (countCards == 5 && rankCounts.size() == 5) {
        std::vector<int> ranks;
        for (const auto& entry : rankCounts) ranks.push_back(entry.first);
        straight = ranks.back() - ranks.front() == 4 ||
                   ranks == std::vector<int>{2, 3, 4, 5, 14};
    }

    if (straight && flush) return HandType::StraightFlush;
    if (!groups.empty() && groups[0] == 4) return HandType::FourOfAKind;
    if (groups.size() == 2 && groups[0] == 3 && groups[1] == 2) return HandType::FullHouse;
    if (flush) return HandType::Flush;
    if (straight) return HandType::Straight;
    if (!groups.empty() && groups[0] == 3) return HandType::ThreeOfAKind;

    int pairCount = 0;
    for (const auto& entry : rankCounts)
        if (entry.second == 2) ++pairCount;
    if (pairCount == 2) return HandType::TwoPair;
    if (pairCount == 1) return HandType::Pair;
    return HandType::HighCard;
}

std::string HandChecker::name(HandType type) const {
    switch (type) {
        case HandType::HighCard: return "High Card";
        case HandType::Pair: return "Pair";
        case HandType::TwoPair: return "Two Pair";
        case HandType::ThreeOfAKind: return "Three of a Kind";
        case HandType::Straight: return "Straight";
        case HandType::Flush: return "Flush";
        case HandType::FullHouse: return "Full House";
        case HandType::FourOfAKind: return "Four of a Kind";
        case HandType::StraightFlush: return "Straight Flush";
    }
    return "Unknown";
}
