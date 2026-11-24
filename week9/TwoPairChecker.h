#pragma once

#include "PokerHandChecker.h"
#include "PokerHandType.h"

class TwoPairChecker : public PokerHandChecker {
public:
    bool checkPokerHand(const std::vector<Card>& cards) const override;
    PokerHandType getHandType() const override;
};
