#pragma once

#include "Deck.h"
#include "HandState.h"

class DrawService {
public:
    void drawToHand(Deck& deck, HandState& handState, int count);
    void refillAndShuffle(Deck& deck);
};
