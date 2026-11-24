#include "Deck.h"

#include <algorithm>
#include <random>
#include <stdexcept>

Deck::Deck() {
    initialize();
}

void Deck::initialize() {
    cards.clear();

    const Suit suits[] = {
        Suit::Hearts,
        Suit::Diamonds,
        Suit::Clubs,
        Suit::Spades
    };

    const Rank ranks[] = {
        Rank::Two,
        Rank::Three,
        Rank::Four,
        Rank::Five,
        Rank::Six,
        Rank::Seven,
        Rank::Eight,
        Rank::Nine,
        Rank::Ten,
        Rank::Jack,
        Rank::Queen,
        Rank::King,
        Rank::Ace
    };

    cards.reserve(52);

    for (Suit suit : suits) {
        for (Rank rank : ranks) {
            cards.push_back({rank, suit});
        }
    }
}

void Deck::shuffle() {
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::shuffle(cards.begin(), cards.end(), generator);
}

Card Deck::drawCard() {
    if (cards.empty()) {
        throw std::out_of_range("Cannot draw from an empty deck");
    }

    Card card = cards.back();
    cards.pop_back();
    return card;
}

bool Deck::isEmpty() const {
    return cards.empty();
}

int Deck::size() const {
    return static_cast<int>(cards.size());
}
