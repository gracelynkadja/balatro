#pragma once
#include <random>
#include <vector>
#include "Hand.h"

// Owns one shuffled 52-card deck for the current round. Cards are never regenerated
// between plays or discards; every replacement comes from the remaining deck.
class HandGenerator {
public:
    Hand generateHand(int handSize = 8);
    Card drawCard();
    std::size_t remainingCards() const;

private:
    void createDeck();
    std::vector<Card> deck_;
    std::size_t nextCard_ = 0;
    bool initialized_ = false;
    std::mt19937 rng_{std::random_device{}()};
};
