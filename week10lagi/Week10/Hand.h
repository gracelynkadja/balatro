#pragma once
#include <vector>
#include "Card.h"

// Hand is the player's current holding. During the run it normally contains 8 cards.
struct Hand {
    std::vector<Card> cards;
};
