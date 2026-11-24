#include "../ChosenHand.h"
#include <cassert>
#include <iostream>

int main() {
    Hand hand;
    hand.cards = {
        {12, 'C'}, {13, 'D'}, {3, 'D'}, {14, 'C'},
        {11, 'H'}, {3, 'C'}, {3, 'S'}, {8, 'H'}
    };

    // Compact input 415 means 4th card, then 1st card, then 5th card.
    ChosenHand chosen(hand);
    assert(chosen.selectCard(3));
    assert(chosen.selectCard(0));
    assert(chosen.selectCard(4));
    assert(chosen.isValid() && chosen.size() == 3);
    const auto cards = chosen.getCards();
    assert(cards[0].rank == 14 && cards[0].suit == 'C');
    assert(cards[1].rank == 12 && cards[1].suit == 'C');
    assert(cards[2].rank == 11 && cards[2].suit == 'H');
    assert(!chosen.selectCard(3));
    std::cout << "Selection order test passed.\n";
}
