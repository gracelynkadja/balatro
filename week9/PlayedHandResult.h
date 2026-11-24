#pragma once

#include "Card.h"
#include "PokerHandType.h"

#include <vector>

struct PlayedHandResult {
    std::vector<Card> cards;
    PokerHandType handType = PokerHandType::None;

    int level = 0;
    int chips = 0;
    int mult = 0;
    int finalScore = 0;
};
