#pragma once

#include "Card.h"
#include "ChosenHand.h"
#include "Deck.h"
#include "HandState.h"
#include "JokerManager.h"
#include "PlayedHandResult.h"
#include "ScoreContext.h"

#include <vector>

class GameManager {
public:
    void runSession();

    void setupJokers();
    Deck createShuffledDeck();
    HandState drawInitialHand(Deck& deck, int handSize);
    void printCards(const std::vector<Card>& cards) const;
    void printGeneratedHand(const HandState& handState) const;
    void printChosenHand(const ChosenHand& chosenHand) const;
    std::vector<int> readSelectedIndices(int handSize, int maxCards = 5) const;
    std::string readPlayerAction() const;
    ChosenHand createChosenHand(
        const HandState& handState,
        const std::vector<int>& selectedIndices
    ) const;
    PlayedHandResult resolveHand(const ChosenHand& chosenHand) const;
    ScoreContext createScoreContext(const PlayedHandResult& result) const;
    void applyJokers(ScoreContext& context) const;
    void printResult(
        const PlayedHandResult& result,
        const ScoreContext& context
    ) const;
    void discardAndRedraw(
        HandState& handState,
        Deck& deck,
        const std::vector<int>& selectedIndices,
        int targetHandSize
    ) const;

private:
    JokerManager jokerManager;

    std::string pokerHandTypeToString(PokerHandType handType) const;
};