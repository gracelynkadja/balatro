#pragma once
#include <iostream>
#include "HandChecker.h"

// Dua Joker yang aktif pada setiap ronde.
class JokerSystem {
public:
    int apply(const ChosenHand& chosen, int score) const {
        HandChecker checker;
        HandType type = checker.check(chosen);

        // Joker 1: Lucky Joker selalu menambahkan 25 poin.
        std::cout << "Lucky Joker: +25 poin\n";
        score += 25;

        // Joker 2: Pair Joker menggandakan skor untuk Pair atau kombinasi lebih tinggi.
        if (static_cast<int>(type) >= static_cast<int>(HandType::Pair)) {
            std::cout << "Pair Joker aktif: skor x2\n";
            score *= 2;
        } else {
            std::cout << "Pair Joker tidak aktif (butuh minimal Pair).\n";
        }
        return score;
    }
};
