#pragma once
#include "TurnInput.h"

// MUTABLE: aturan penghitungan skor dasar.
class IScoringRule {
public:
    virtual ~IScoringRule() = default;
    virtual int computeBaseScore(const TurnInput& input) const = 0;
};
