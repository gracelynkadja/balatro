#include "HighCardChecker.h"

bool HighCardChecker::checkPokerHand(const std::vector<Card>& cards) const {
    return !cards.empty();
}

PokerHandType HighCardChecker::getHandType() const {
    return PokerHandType::HighCard;
}
