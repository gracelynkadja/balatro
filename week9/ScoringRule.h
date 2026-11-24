#pragma once

#include "PokerHandType.h"
#include "HandScoreTable.h"

class ScoringRule {
public:
    explicit ScoringRule(const HandScoreTable& handScoreTable);

    int calculateScore(PokerHandType handType) const;

    int getChips(PokerHandType handType) const;
    int getMult(PokerHandType handType) const;
    int getLevel(PokerHandType handType) const;

private:
    const HandScoreTable& handScoreTable;
};