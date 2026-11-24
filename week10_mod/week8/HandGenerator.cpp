#include <algorithm>
#include <random>
#include <stdexcept>
#include "HandGenerator.h"

HandGenerator::HandGenerator() : nextCard(0) {
    startNewRound();
}

void HandGenerator::startNewRound() {
    deck.clear();
    const char suits[] = {'H', 'D', 'C', 'S'};
    for (char suit : suits) {
        for (int rank = 2; rank <= 14; ++rank) {
            deck.push_back({rank, suit});
        }
    }
    static std::mt19937 rng(std::random_device{}());
    std::shuffle(deck.begin(), deck.end(), rng);
    nextCard = 0;
}

Hand HandGenerator::generateHand(int handSize) {
    Hand hand;
    for (int i = 0; i < handSize && nextCard < deck.size(); ++i) {
        hand.cards.push_back(drawCard());
    }
    return hand;
}

Card HandGenerator::drawCard() {
    if (nextCard >= deck.size()) {
        throw std::runtime_error("Deck sudah habis.");
    }
    return deck[nextCard++];
}
