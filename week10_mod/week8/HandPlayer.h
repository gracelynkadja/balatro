#pragma once
#include "Hand.h"
#include "ChosenHand.h"

class HandPlayer {
public:
    ChosenHand chooseHand(const Hand& hand);
    void playHand(const ChosenHand& chosen);
    void showHand(const Hand& hand) const;
};
