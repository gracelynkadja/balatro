#include "GameManager.h"

#include "ChosenHand.h"
#include "Deck.h"
#include "DiscardService.h"
#include "DrawService.h"
#include "FlatChipJoker.h"
#include "HandResolver.h"
#include "HandScoreTable.h"
#include "HandState.h"
#include "PairJoker.h"
#include "PlayedHandResult.h"
#include "PokerHandEvaluator.h"
#include "RunSessionService.h"
#include "ScoreContext.h"
#include "ScoringRule.h"

#include <iostream>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>

void GameManager::runSession() {
    BlindConfig config; // TODO: inject or configure
    RunSessionService service(*this, config);
    service.runSession();
}

// ===================== SETUP =====================

void GameManager::setupJokers() {
    jokerManager.addJoker(std::make_unique<PairJoker>());
    jokerManager.addJoker(std::make_unique<FlatChipJoker>());
}

Deck GameManager::createShuffledDeck() {
    Deck deck;
    deck.initialize();
    deck.shuffle();
    return deck;
}

HandState GameManager::drawInitialHand(Deck& deck, int handSize) {
    HandState handState;
    DrawService drawService;
    drawService.drawToHand(deck, handState, handSize);
    return handState;
}

// ===================== INPUT =====================

std::vector<int> GameManager::readSelectedIndices(int handSize, int maxCards) const {
    std::cout << "\nEnter up to " << maxCards << " card indices to select, separated by spaces: ";

    std::string input;
    std::getline(std::cin, input);

    std::istringstream stream(input);
    std::set<int> seenIndices;
    std::vector<int> indices;
    int index = 0;

    while (stream >> index) {
        if (index < 0 || index >= handSize) {
            continue;
        }

        if (seenIndices.insert(index).second) {
            indices.push_back(index);
        }
    }

    if (static_cast<int>(indices.size()) > maxCards) {
        std::cout << "Too many cards selected, using first " << maxCards << ".\n";
        indices.resize(maxCards);
    }

    return indices;
}

std::string GameManager::readPlayerAction() const {
    std::cout << "\nChoose action: (P)lay or (D)iscard: ";

    std::string input;
    std::getline(std::cin, input);

    if (input == "P" || input == "p" || input == "Play" || input == "play") {
        return "PLAY";
    }
    if (input == "D" || input == "d" || input == "Discard" || input == "discard") {
        return "DISCARD";
    }

    return "INVALID";
}

ChosenHand GameManager::createChosenHand(
    const HandState& handState,
    const std::vector<int>& selectedIndices
) const {
    ChosenHand chosenHand;

    for (int index : selectedIndices) {
        chosenHand.addCard(handState.getCards()[index]);
    }

    return chosenHand;
}

// ===================== RESOLVE =====================

PlayedHandResult GameManager::resolveHand(
    const ChosenHand& chosenHand
) const {
    PokerHandEvaluator evaluator;
    HandScoreTable handScoreTable;
    ScoringRule scoringRule(handScoreTable);
    HandResolver handResolver(evaluator, scoringRule);

    return handResolver.resolve(chosenHand);
}

ScoreContext GameManager::createScoreContext(
    const PlayedHandResult& result
) const {
    ScoreContext context;
    context.cards = result.cards;
    context.handType = result.handType;
    context.level = result.level;
    context.chips = result.chips;
    context.mult = result.mult;
    return context;
}

void GameManager::applyJokers(ScoreContext& context) const {
    jokerManager.notifyScoreCalculatedWithLog(context);
}

// ===================== OUTPUT =====================

void GameManager::printGeneratedHand(const HandState& handState) const {
    std::cout << "Generated hand:\n";
    printCards(handState.getCards());
}

void GameManager::printChosenHand(const ChosenHand& chosenHand) const {
    std::cout << "\nChosen hand:\n";
    printCards(chosenHand.getSelectedCards());
}

void GameManager::printResult(
    const PlayedHandResult& result,
    const ScoreContext& context
) const {
    std::cout << "\nPlayed hand result:\n";
    std::cout << "Hand type: "
              << pokerHandTypeToString(result.handType) << "\n";

    std::cout << "Level: " << result.level << "\n";

    std::cout << "=== Base Score ===\n";
    std::cout << "Chips: " << result.chips << "\n";
    std::cout << "Mult : " << result.mult << "\n";
    std::cout << "Score: " << result.finalScore << "\n";

    std::cout << "\n=== After Joker ===\n";
    std::cout << "Chips: " << context.chips << "\n";
    std::cout << "Mult : " << context.mult << "\n";
    std::cout << "Score: " << context.getFinalScore() << "\n";

    std::cout << "\nJokers active: " << jokerManager.size() << "\n";
}

void GameManager::printCards(const std::vector<Card>& cards) const {
    for (int i = 0; i < static_cast<int>(cards.size()); ++i) {
        std::cout << i << ": " << cards[i].toString() << "\n";
    }
}

// ===================== DISCARD =====================

void GameManager::discardAndRedraw(
    HandState& handState,
    Deck& deck,
    const std::vector<int>& selectedIndices,
    int targetHandSize
) const {
    DiscardService discardService;
    discardService.discardAndRedraw(
        handState,
        deck,
        selectedIndices,
        targetHandSize
    );
}

// ===================== UTIL =====================

std::string GameManager::pokerHandTypeToString(
    PokerHandType handType
) const {
    switch (handType) {
    case PokerHandType::HighCard: return "High Card";
    case PokerHandType::Pair: return "Pair";
    case PokerHandType::TwoPair: return "Two Pair";
    case PokerHandType::ThreeOfAKind: return "Three of a Kind";
    case PokerHandType::Straight: return "Straight";
    case PokerHandType::Flush: return "Flush";
    case PokerHandType::FullHouse: return "Full House";
    case PokerHandType::FourOfAKind: return "Four of a Kind";
    case PokerHandType::StraightFlush: return "Straight Flush";
    case PokerHandType::RoyalFlush: return "Royal Flush";
    case PokerHandType::FiveOfAKind: return "Five of a Kind";
    case PokerHandType::FlushHouse: return "Flush House";
    case PokerHandType::FlushFive: return "Flush Five";
    case PokerHandType::None: return "None";
    }

    return "None";
}