#pragma once
#include "IRewardRule.h"

// Implementasi awal: reward = baseScore.
class DirectRewardRule : public IRewardRule {
public:
    int computeReward(int baseScore) const override {
        return baseScore;
    }
};
