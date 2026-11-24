#include <algorithm>
#include <map>
#include <vector>
#include "HandChecker.h"

HandType HandChecker::check(const ChosenHand& chosen) const {
    std::vector<Card> cards = chosen.getCards();
    int n = (int)cards.size();
    if (n == 0) return HandType::HighCard;

    // Hitung kemunculan tiap rank
    std::map<int, int> count;
    for (const Card& c : cards) count[c.rank]++;
    std::vector<int> groups;                       // jumlah kartu per rank, urut desc
    for (auto& p : count) groups.push_back(p.second);
    std::sort(groups.rbegin(), groups.rend());

    // Flush & Straight hanya valid jika 5 kartu
    bool flush = (n == 5);
    for (const Card& c : cards) if (c.suit != cards[0].suit) flush = false;

    bool straight = false;
    if (n == 5 && count.size() == 5) {
        std::vector<int> r;
        for (auto& p : count) r.push_back(p.first);   // sudah terurut asc
        straight = (r[4] - r[0] == 4) ||
                   (r == std::vector<int>{2, 3, 4, 5, 14});  // A-2-3-4-5
    }

    if (straight && flush)                 return HandType::StraightFlush;
    if (groups[0] == 4)                    return HandType::FourOfAKind;
    if (groups[0] == 3 && groups.size() > 1 && groups[1] == 2)
                                           return HandType::FullHouse;
    if (flush)                             return HandType::Flush;
    if (straight)                          return HandType::Straight;
    if (groups[0] == 3)                    return HandType::ThreeOfAKind;
    if (groups[0] == 2 && groups.size() > 1 && groups[1] == 2)
                                           return HandType::TwoPair;
    if (groups[0] == 2)                    return HandType::Pair;
    return HandType::HighCard;
}

std::string HandChecker::name(HandType t) const {
    switch (t) {
        case HandType::StraightFlush: return "Straight Flush";
        case HandType::FourOfAKind:   return "Four of a Kind";
        case HandType::FullHouse:     return "Full House";
        case HandType::Flush:         return "Flush";
        case HandType::Straight:      return "Straight";
        case HandType::ThreeOfAKind:  return "Three of a Kind";
        case HandType::TwoPair:       return "Two Pair";
        case HandType::Pair:          return "Pair";
        default:                      return "High Card";
    }
}
