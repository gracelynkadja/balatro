#pragma once
#include "IRewardRule.h"

// Implementasi konkret: gold = setengah dari damage yang berhasil dikenakan.
class SimpleRewardRule : public IRewardRule {
public:
    int computeGold(const CombatResult& result) const override {
        return result.damageDealt / 2;
    }
};
