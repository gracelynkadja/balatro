#include "ChosenHand.h"

void ChosenHand::addCard(const Card& card) {
    selectedCards.push_back(card);
}

void ChosenHand::removeCardAt(int index) {
    if (index < 0 || index >= size()) {
        return;
    }

    selectedCards.erase(selectedCards.begin() + index);
}

void ChosenHand::clear() {
    selectedCards.clear();
}

const std::vector<Card>& ChosenHand::getSelectedCards() const {
    return selectedCards;
}

int ChosenHand::size() const {
    return static_cast<int>(selectedCards.size());
}
