#include "HandGenerator.h"
#include <algorithm>
#include <stdexcept>

void HandGenerator::createDeck() {
    deck_.clear();
    const char suits[] = {'H', 'D', 'C', 'S'};
    for (char suit : suits)
        for (int rank = 2; rank <= 14; ++rank)
            deck_.push_back({rank, suit});
    std::shuffle(deck_.begin(), deck_.end(), rng_);
    nextCard_ = 0;
    initialized_ = true;
}

Hand HandGenerator::generateHand(int handSize) {
    if (!initialized_) createDeck();
    Hand hand;
    for (int i = 0; i < handSize && nextCard_ < deck_.size(); ++i)
        hand.cards.push_back(drawCard());
    return hand;
}

Card HandGenerator::drawCard() {
    if (!initialized_) createDeck();
    if (nextCard_ >= deck_.size())
        throw std::runtime_error("Kartu di deck sudah habis.");
    return deck_[nextCard_++];
}

std::size_t HandGenerator::remainingCards() const {
    return initialized_ && nextCard_ <= deck_.size() ? deck_.size() - nextCard_ : 0;
}
