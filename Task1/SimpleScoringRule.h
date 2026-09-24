#pragma once
#include "IScoringRule.h"

class SimpleScoringRule : public IScoringRule {
public:
    int computeBaseScore(const TurnInput& input) const override {
        return input.value;
    }
};
