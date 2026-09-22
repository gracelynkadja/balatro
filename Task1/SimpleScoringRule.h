#pragma once
#include "IScoringRule.h"

// Skor dasar = nilai input.
class SimpleScoringRule : public IScoringRule {
public:
    int computeBaseScore(const TurnInput& input) const override {
        return input.value;
    }
};
