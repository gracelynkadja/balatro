#pragma once
#include "TurnInput.h"

class IScoringRule {
public:
    virtual ~IScoringRule() = default;
    virtual int computeBaseScore(const TurnInput& input) const = 0;
};
