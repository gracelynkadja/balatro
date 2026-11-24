#pragma once

#include "Card.h"

#include <vector>

class ChosenHand {
public:
    void addCard(const Card& card);
    void removeCardAt(int index);
    void clear();

    const std::vector<Card>& getSelectedCards() const;
    int size() const;

private:
    std::vector<Card> selectedCards;
};
