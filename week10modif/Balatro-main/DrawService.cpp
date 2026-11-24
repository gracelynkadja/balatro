#include "DrawService.h"

void DrawService::drawToHand(Deck& deck, HandState& handState, int count) {
    for (int i = 0; i < count && !deck.isEmpty(); ++i) {
        handState.addCard(deck.drawCard());
    }
}

void DrawService::refillAndShuffle(Deck& deck) {
    deck.initialize();
    deck.shuffle();
}
