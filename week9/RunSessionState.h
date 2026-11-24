#pragma once

#include "Deck.h"
#include "HandState.h"

struct RunSessionState {
    Deck deck;
    HandState handState;
    int currentScore = 0;
};