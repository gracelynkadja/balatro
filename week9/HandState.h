#pragma once

#include "Card.h"

#include <vector>

class HandState {
public:
    void addCard(const Card& card);
    void removeCardAt(int index);
    void clear();

    const std::vector<Card>& getCards() const;
    int size() const;

private:
    std::vector<Card> cards;
};
