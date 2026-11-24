#pragma once
#include "HandChecker.h"
#include "ScoringRule.h"

// Resolves the selected cards into a HandRank, then asks ScoringRule for the base score.
class HandResolver {
public:
    HandScoreResult resolve(const ChosenHand& chosen) const;

private:
    HandChecker checker_;
    ScoringRule scoringRule_;
};
