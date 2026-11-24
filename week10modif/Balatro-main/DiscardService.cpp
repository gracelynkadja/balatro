#include "DiscardService.h"

#include "DrawService.h"

#include <algorithm>

void DiscardService::discardCardsAtIndices(HandState& handState, const std::vector<int>& indices) {
    std::vector<int> sortedIndices = indices;
    std::sort(sortedIndices.begin(), sortedIndices.end(), std::greater<int>());

    for (int index : sortedIndices) {
        handState.removeCardAt(index);
    }
}

void DiscardService::discardAndRedraw(HandState& handState, Deck& deck, const std::vector<int>& indices, int targetHandSize){
    discardCardsAtIndices(handState, indices);

    const int cardsNeeded = targetHandSize - handState.size();
    if (cardsNeeded <= 0) {
        return;
    }

    DrawService drawService;
    drawService.drawToHand(deck, handState, cardsNeeded);
}
