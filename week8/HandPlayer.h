#pragma once
#include "Hand.h"
#include "ChosenHand.h"
class HandPlayer {
public:
    // Pilih 5 kartu dari hand (di sini: acak sederhana, bisa diganti input user)
    ChosenHand chooseHand(const Hand& hand);
    void playHand(const ChosenHand& chosen);
};
