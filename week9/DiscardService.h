#pragma once

#include "Deck.h"
#include "HandState.h"

#include <vector>

class DiscardService {
public:
    void discardCardsAtIndices(
        HandState& handState,
        const std::vector<int>& indices
    );

    void discardAndRedraw(
        HandState& handState,
        Deck& deck,
        const std::vector<int>& indices,
        int targetHandSize
    );
};
