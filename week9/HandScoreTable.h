#pragma once

#include <unordered_map>
#include "PokerHandType.h"
#include "HandScoreData.h"

class HandScoreTable {
public:
    HandScoreTable();

    const HandScoreData& getData(PokerHandType handType) const;

    void upgradeHand(
        PokerHandType handType,
        int chipsIncrease,
        int multIncrease
    );

private:
    std::unordered_map<PokerHandType, HandScoreData> table;
};