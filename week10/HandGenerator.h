#pragma once
#include "Hand.h"

class HandGenerator {
public:
    Hand generateHand(int handSize = 8);
    Card drawCard();

private:
    void createDeck();
    std::vector<Card> deck;
    size_t nextCard = 0;
};
