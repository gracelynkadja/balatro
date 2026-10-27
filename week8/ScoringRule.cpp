#include <iostream>
#include "ScoringRule.h"

int ScoringRule::scoreHand(const ChosenHand& chosen) {
    HandType type = checker.check(chosen);
    // {chips, mult} per jenis hand
    static const int chips[] = {5, 10, 20, 30, 30, 35, 40, 60, 100};
    static const int mult[]  = {1,  2,  2,  3,  4,  4,  4,  7,   8};
    int i = (int)type;

    int total = chips[i];
    for (const Card& c : chosen.getCards())
        total += (c.rank >= 14) ? 11 : (c.rank >= 11 ? 10 : c.rank);

    std::cout << "Hand type: " << checker.name(type) << "\n";
    return total * mult[i];
}
