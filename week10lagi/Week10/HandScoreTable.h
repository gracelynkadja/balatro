#pragma once
#include "HandChecker.h"

struct HandScoreData {
    int baseChips;
    int baseMult;
};

class HandScoreTable {
public:
    HandScoreData get(HandType type) const;
};
