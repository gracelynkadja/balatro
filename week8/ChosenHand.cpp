#include <algorithm>
#include <iostream>
#include <string>
#include "ChosenHand.h"

ChosenHand::ChosenHand(const Hand& source) : source(source) {}

bool ChosenHand::selectCard(int index) {
    if (index < 0 || index >= (int)source.cards.size()) return false;
    if (isSelected(index)) return false;
    if ((int)selectedIndices.size() >= MAX_CARDS) return false;
    selectedIndices.push_back(index);
    return true;
}

bool ChosenHand::deselectCard(int index) {
    auto it = std::find(selectedIndices.begin(), selectedIndices.end(), index);
    if (it == selectedIndices.end()) return false;
    selectedIndices.erase(it);
    return true;
}

void ChosenHand::clear() { selectedIndices.clear(); }

bool ChosenHand::isSelected(int index) const {
    return std::find(selectedIndices.begin(), selectedIndices.end(), index)
           != selectedIndices.end();
}

bool ChosenHand::isValid() const {
    return !selectedIndices.empty() && (int)selectedIndices.size() <= MAX_CARDS;
}

int ChosenHand::size() const { return (int)selectedIndices.size(); }

std::vector<Card> ChosenHand::getCards() const {
    std::vector<Card> result;
    for (int i : selectedIndices) result.push_back(source.cards[i]);
    return result;
}

static std::string rankName(int rank) {
    switch (rank) {
        case 11: return "J";
        case 12: return "Q";
        case 13: return "K";
        case 14: return "A";
        default: return std::to_string(rank);
    }
}

void ChosenHand::print() const {
    for (const Card& c : getCards()) std::cout << rankName(c.rank) << c.suit << " ";
    std::cout << "\n";
}
