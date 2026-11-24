#pragma once

#include "PokerHandChecker.h"
#include "PokerHandType.h"

class PairChecker : public PokerHandChecker {
public:
    bool checkPokerHand(const std::vector<Card>& cards) const override;
    PokerHandType getHandType() const override;
};
