#pragma once
#include <vector>
#include "Hand.h"

// Keeps the source holding and the player's selected zero-based positions.
// Selection order is preserved, e.g. input 415 means positions 4, 1, then 5.
class ChosenHand {
public:
    static constexpr int MAX_CARDS = 5;

    ChosenHand() = default;
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
    Hand source_;
    std::vector<int> selectedIndices_;
};
