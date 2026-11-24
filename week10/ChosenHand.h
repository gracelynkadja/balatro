#pragma once
#include <vector>
#include "Hand.h"

class ChosenHand {
public:
    static const int MAX_CARDS = 5;
    explicit ChosenHand(const Hand& source);
    bool selectCard(int index);
    bool deselectCard(int index);
    void clear();
    bool isSelected(int index) const;
    bool isValid() const;
    int size() const;
    std::vector<Card> getCards() const;
    std::vector<int> getSelectedIndices() const;
    void print() const;

private:
    Hand source;
    std::vector<int> selectedIndices;
};
