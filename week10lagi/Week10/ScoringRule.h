#pragma once
#include "ChosenHand.h"
#include "HandScoreTable.h"

struct HandScoreResult {
    HandType handType = HandType::HighCard;
    int baseChips = 0;
    int cardChips = 0;
    int chips = 0;
    int mult = 1;
    int baseScore = 0;
};

class ScoringRule {
public:
    HandScoreResult calculate(const ChosenHand& chosen, HandType type) const;

private:
    HandScoreTable scoreTable_;
};
