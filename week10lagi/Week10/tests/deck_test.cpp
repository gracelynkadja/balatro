#include "../HandGenerator.h"
#include <cassert>
#include <iostream>
#include <set>
#include <string>

int main() {
    HandGenerator generator;
    Hand opening = generator.generateHand(8);
    assert(opening.cards.size() == 8);

    std::set<std::string> keys;
    for (const Card& card : opening.cards)
        keys.insert(std::to_string(card.rank) + card.suit);
    assert(keys.size() == 8);
    assert(generator.remainingCards() == 44);

    Card replacement = generator.drawCard();
    assert(keys.insert(std::to_string(replacement.rank) + replacement.suit).second);
    assert(generator.remainingCards() == 43);
    std::cout << "Persistent 52-card deck test passed.\n";
}
