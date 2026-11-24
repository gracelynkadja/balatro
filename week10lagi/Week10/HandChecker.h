#pragma once
#include <string>
#include "ChosenHand.h"

enum class HandType {
    HighCard, Pair, TwoPair, ThreeOfAKind, Straight,
    Flush, FullHouse, FourOfAKind, StraightFlush
};

// Week10 terminology: HandRank is the same classification enum.
using HandRank = HandType;

class HandChecker {
public:
    HandType check(const ChosenHand& chosen) const;
    std::string name(HandType type) const;
};
