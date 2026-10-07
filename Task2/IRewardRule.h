#pragma once
#include "CombatResult.h"

// MUTABLE: aturan menghitung gold yang didapat dari hasil combat.
class IRewardRule {
public:
    virtual ~IRewardRule() = default;
    virtual int computeGold(const CombatResult& result) const = 0;
};
