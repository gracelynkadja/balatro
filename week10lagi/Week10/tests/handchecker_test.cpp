#include "../HandChecker.h"
#include <cassert>
#include <iostream>

int main() {
    Hand hand;
    hand.cards = {
        {12, 'C'}, {13, 'D'}, {3, 'D'}, {14, 'C'},
        {11, 'H'}, {3, 'C'}, {3, 'S'}, {8, 'H'}
    };

    ChosenHand threeOfAKind(hand);
    assert(threeOfAKind.selectCard(2)); // 3♦
    assert(threeOfAKind.selectCard(5)); // 3♣
    assert(threeOfAKind.selectCard(6)); // 3♠

    HandChecker checker;
    assert(checker.check(threeOfAKind) == HandType::ThreeOfAKind);
    std::cout << "HandRank checker test passed.\n";
}
