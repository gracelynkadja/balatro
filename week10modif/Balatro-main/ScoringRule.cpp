#include "ScoringRule.h"

ScoringRule::ScoringRule(const HandScoreTable& handScoreTable)
    : handScoreTable(handScoreTable)
{
}

int ScoringRule::calculateScore(PokerHandType handType) const {
    const HandScoreData& data = handScoreTable.getData(handType);
    return data.chips * data.mult;
}

int ScoringRule::getChips(PokerHandType handType) const {
    return handScoreTable.getData(handType).chips;
}

int ScoringRule::getMult(PokerHandType handType) const {
    return handScoreTable.getData(handType).mult;
}

int ScoringRule::getLevel(PokerHandType handType) const {
    return handScoreTable.getData(handType).level;
}