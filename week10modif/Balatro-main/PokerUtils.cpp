#include "PokerUtils.h"

std::unordered_map<Rank, int> countRanks(const std::vector<Card>& cards) {
    std::unordered_map<Rank, int> rankCount;

    for (const Card& card : cards) {
        ++rankCount[card.rank];
    }

    return rankCount;
}

std::unordered_map<Suit, int> countSuits(const std::vector<Card>& cards) {
    std::unordered_map<Suit, int> suitCount;

    for (const Card& card : cards) {
        ++suitCount[card.suit];
    }

    return suitCount;
}

bool hasNOfAKind(const std::unordered_map<Rank, int>& rankCount, int n) {
    for (const auto& entry : rankCount) {
        if (entry.second == n) {
            return true;
        }
    }

    return false;
}

bool hasAtLeastNOfAKind(const std::unordered_map<Rank, int>& rankCount, int n) {
    for (const auto& entry : rankCount) {
        if (entry.second >= n) {
            return true;
        }
    }

    return false;
}

int countPairs(const std::unordered_map<Rank, int>& rankCount) {
    int pairs = 0;

    for (const auto& entry : rankCount) {
        if (entry.second == 2) {
            ++pairs;
        }
    }

    return pairs;
}
