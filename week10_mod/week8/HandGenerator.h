#pragma once
#include <vector>
#include "Hand.h"

class HandGenerator {
public:
    HandGenerator();
    void startNewRound();
    Hand generateHand(int handSize = 8);
    Card drawCard();

private:
    std::vector<Card> deck;
    size_t nextCard;
};
