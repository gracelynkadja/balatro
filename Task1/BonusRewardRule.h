#pragma once
#include "IRewardRule.h"

// Modification 2: reward TIDAK sama dengan baseScore lagi.
// reward = baseScore + 2
class BonusRewardRule : public IRewardRule {
public:
    int computeReward(int baseScore) const override {
        return baseScore + 2;
    }
};
