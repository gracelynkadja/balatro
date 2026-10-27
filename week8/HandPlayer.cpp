#include <iostream>
#include <algorithm>
#include <numeric>
#include <random>
#include "HandPlayer.h"

ChosenHand HandPlayer::chooseHand(const Hand& hand) {
    std::vector<int> idx(hand.cards.size());
    std::iota(idx.begin(), idx.end(), 0);
    static std::mt19937 rng(std::random_device{}());
    std::shuffle(idx.begin(), idx.end(), rng);

    ChosenHand chosen(hand);
    for (int i = 0; i < ChosenHand::MAX_CARDS && i < (int)idx.size(); ++i)
        chosen.selectCard(idx[i]);
    return chosen;
}

void HandPlayer::playHand(const ChosenHand& chosen) {
    if (!chosen.isValid()) {
        std::cout << "Invalid hand: pilih 1-" << ChosenHand::MAX_CARDS << " kartu.\n";
        return;
    }
    std::cout << "Playing hand: ";
    chosen.print();
}
