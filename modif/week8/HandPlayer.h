#pragma once
#include "Hand.h"
#include "ChosenHand.h"

class HandPlayer {
public:
    // Menampilkan kartu dan menerima pilihan 1-5 kartu dari input pemain.
    ChosenHand chooseHand(const Hand& hand);
    void playHand(const ChosenHand& chosen);
};
