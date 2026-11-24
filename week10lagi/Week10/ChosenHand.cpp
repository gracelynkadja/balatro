#include "ChosenHand.h"
#include <algorithm>
#include <iostream>

ChosenHand::ChosenHand(const Hand& source) : source_(source) {}

bool ChosenHand::selectCard(int index) {
    if (index < 0 || index >= static_cast<int>(source_.cards.size())) return false;
    if (isSelected(index) || size() >= MAX_CARDS) return false;
    selectedIndices_.push_back(index);
    return true;
}

bool ChosenHand::deselectCard(int index) {
    const auto it = std::find(selectedIndices_.begin(), selectedIndices_.end(), index);
    if (it == selectedIndices_.end()) return false;
    selectedIndices_.erase(it);
    return true;
}

void ChosenHand::clear() { selectedIndices_.clear(); }

bool ChosenHand::isSelected(int index) const {
    return std::find(selectedIndices_.begin(), selectedIndices_.end(), index) != selectedIndices_.end();
}

bool ChosenHand::isValid() const {
    return !selectedIndices_.empty() && size() <= MAX_CARDS;
}

int ChosenHand::size() const { return static_cast<int>(selectedIndices_.size()); }

std::vector<Card> ChosenHand::getCards() const {
    std::vector<Card> result;
    result.reserve(selectedIndices_.size());
    for (int index : selectedIndices_) result.push_back(source_.cards.at(static_cast<std::size_t>(index)));
    return result;
}

std::vector<int> ChosenHand::getSelectedIndices() const { return selectedIndices_; }

void ChosenHand::print() const {
    for (const Card& card : getCards()) std::cout << '[' << CardToString(card) << "] ";
    std::cout << '\n';
}
