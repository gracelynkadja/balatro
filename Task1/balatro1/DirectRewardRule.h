#pragma once
#include "IRewardRule.h"

class DirectRewardRule : public IRewardRule {
public:
    int computeReward(int baseScore) const override {
        return baseScore;
    }
};
