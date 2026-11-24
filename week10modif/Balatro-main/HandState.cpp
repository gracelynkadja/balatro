#include "HandState.h"

void HandState::addCard(const Card& card) {
    cards.push_back(card);
}

void HandState::removeCardAt(int index) {
    if (index < 0 || index >= size()) {
        return;
    }

    cards.erase(cards.begin() + index);
}

void HandState::clear() {
    cards.clear();
}

const std::vector<Card>& HandState::getCards() const {
    return cards;
}

int HandState::size() const {
    return static_cast<int>(cards.size());
}
