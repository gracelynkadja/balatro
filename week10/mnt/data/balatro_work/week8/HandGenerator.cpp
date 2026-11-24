#include <algorithm>
#include <random>
#include <stdexcept>
#include "HandGenerator.h"

void HandGenerator::createDeck() {
    deck.clear();
    const char suits[] = {'H', 'D', 'C', 'S'};
    for (char suit : suits)
        for (int rank = 2; rank <= 14; ++rank)
            deck.push_back({rank, suit});
    static std::mt19937 rng(std::random_device{}());
    std::shuffle(deck.begin(), deck.end(), rng);
    nextCard = 0;
}

Hand HandGenerator::generateHand(int handSize) {
    createDeck();
    Hand hand;
    for (int i = 0; i < handSize && nextCard < deck.size(); ++i)
        hand.cards.push_back(drawCard());
    return hand;
}

Card HandGenerator::drawCard() {
    if (nextCard >= deck.size())
        throw std::runtime_error("Kartu di deck sudah habis.");
    return deck[nextCard++];
}
