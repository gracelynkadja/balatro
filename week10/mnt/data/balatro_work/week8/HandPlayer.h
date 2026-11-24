#pragma once
#include <vector>
#include <string>
#include "Hand.h"
#include "ChosenHand.h"

class HandPlayer {
public:
    ChosenHand chooseHand(const Hand& hand);
    std::vector<int> chooseDiscard(const Hand& hand);
    void playHand(const ChosenHand& chosen);

private:
    std::vector<int> chooseIndices(const Hand& hand, const std::string& prompt);
    void showHand(const Hand& hand) const;
};
