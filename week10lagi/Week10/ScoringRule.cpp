#include "ScoringRule.h"
#include <algorithm>
#include <map>
#include <set>
#include <vector>

HandScoreResult ScoringRule::calculate(const ChosenHand& chosen, HandType type) const {
    HandScoreResult result;
    result.handType = type;
    const HandScoreData base = scoreTable_.get(type);
    result.baseChips = base.baseChips;
    result.mult = base.baseMult;

    const std::vector<Card> cards = chosen.getCards();
    std::map<int, int> counts;
    for (const Card& card : cards) ++counts[card.rank];

    std::set<int> scoringRanks;
    auto addRanksWithCount = [&counts, &scoringRanks](int wantedCount) {
        for (const auto& entry : counts)
            if (entry.second == wantedCount) scoringRanks.insert(entry.first);
    };

    switch (type) {
        case HandType::HighCard: {
            int highest = 0;
            for (const Card& card : cards) highest = std::max(highest, card.rank);
            if (!cards.empty()) scoringRanks.insert(highest);
            break;
        }
        case HandType::Pair:
        case HandType::TwoPair:
            addRanksWithCount(2);
            break;
        case HandType::ThreeOfAKind:
            addRanksWithCount(3);
            break;
        case HandType::FourOfAKind:
            addRanksWithCount(4);
            break;
        case HandType::Straight:
        case HandType::Flush:
        case HandType::FullHouse:
        case HandType::StraightFlush:
            for (const Card& card : cards) scoringRanks.insert(card.rank);
            break;
    }

    for (const Card& card : cards)
        if (scoringRanks.count(card.rank) > 0)
            result.cardChips += CardChipValue(card);

    result.chips = result.baseChips + result.cardChips;
    result.baseScore = result.chips * result.mult;
    return result;
}
