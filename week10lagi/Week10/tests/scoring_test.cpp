#include "../HandResolver.h"
#include <cassert>
#include <iostream>

int main() {
    Hand hand;
    hand.cards = {{14,'H'}, {2,'S'}, {4,'C'}, {6,'D'}, {8,'H'}};
    ChosenHand chosen(hand);
    for (int i = 0; i < 5; ++i) assert(chosen.selectCard(i));

    HandResolver resolver;
    const HandScoreResult result = resolver.resolve(chosen);
    assert(result.handType == HandType::HighCard);
    assert(result.baseChips == 5);
    assert(result.cardChips == 11);
    assert(result.chips == 16);
    assert(result.mult == 1);
    assert(result.baseScore == 16);
    std::cout << "Scoring test passed.\n";
}
