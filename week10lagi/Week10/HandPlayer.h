#pragma once
#include <string>
#include <vector>
#include "ChosenHand.h"

// Handles console input and translates compact input such as 415 into positions 4,1,5.
class HandPlayer {
public:
    void showHand(const Hand& hand) const;
    bool readAction(int discardsRemaining, char& action) const;
    bool chooseHand(const Hand& hand, ChosenHand& chosen) const;
    bool chooseDiscard(const Hand& hand, std::vector<int>& indices) const;

private:
    bool chooseIndices(const Hand& hand, const std::string& prompt,
                       std::vector<int>& indices) const;
};
