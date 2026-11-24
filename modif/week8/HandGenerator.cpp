#include <iostream>
#include <algorithm>
#include <random>
#include "HandGenerator.h"

Hand HandGenerator::generateHand(int handSize) {
    std::cout << "Generating hand...\n";

    // Buat satu deck standar 52 kartu
    std::vector<Card> deck;
    const char suits[] = {'H', 'D', 'C', 'S'};
    for (char s : suits)
        for (int r = 2; r <= 14; ++r)
            deck.push_back({r, s});

    // Kocok deck (static supaya seed hanya dibuat sekali)
    static std::mt19937 rng(std::random_device{}());
    std::shuffle(deck.begin(), deck.end(), rng);

    // Ambil handSize kartu teratas
    Hand hand;
    for (int i = 0; i < handSize && i < (int)deck.size(); ++i)
        hand.cards.push_back(deck[i]);
    return hand;
}
