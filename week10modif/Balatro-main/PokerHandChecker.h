#pragma once
#include <vector>
#include "Card.h"
#include "PokerHandType.h"

class PokerHandChecker {
public:
    virtual ~PokerHandChecker() = default;
    virtual bool checkPokerHand(const std::vector<Card>& cards) const = 0;
    virtual PokerHandType getHandType() const = 0;
};
