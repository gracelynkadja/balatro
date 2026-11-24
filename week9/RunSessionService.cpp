#include "RunSessionService.h"

#include "ChosenHand.h"
#include "PlayedHandResult.h"
#include "ScoreContext.h"

#include <iostream>
#include <vector>

RunSessionService::RunSessionService(GameManager& gm, BlindConfig cfg)
    : gameManager(gm), config(cfg) {}

void RunSessionService::runSession() {
    initializeSession();
    runSessionLoop();
    printSessionResult();
}

void RunSessionService::initializeSession() {
    gameManager.setupJokers();
    state.deck = gameManager.createShuffledDeck();
    state.handState = gameManager.drawInitialHand(state.deck, 8);
}

void RunSessionService::runSessionLoop() {
    while (!isSessionEnded()) {
        printSessionStatus();
        PlayerActionRequest request = readPlayerActionRequest();
        if (canPerformAction(request.action)) {
            processPlayerAction(request);
        } else {
            std::cout << "Cannot perform that action.\n";
        }
    }
}

bool RunSessionService::isSessionEnded() {
    return state.currentScore >= config.minimumScore || config.remainingPlays == 0;
}

PlayerActionRequest RunSessionService::readPlayerActionRequest() {
    const std::vector<int> selectedIndices = gameManager.readSelectedIndices(state.handState.size(), config.maxSelectedCards);
    ChosenHand chosenHand = gameManager.createChosenHand(state.handState, selectedIndices);
    gameManager.printChosenHand(chosenHand);
    std::string actionStr = gameManager.readPlayerAction();
    PlayerAction action = (actionStr == "PLAY") ? PlayerAction::PLAY : PlayerAction::DISCARD;
    return {action, selectedIndices};
}

bool RunSessionService::canPerformAction(PlayerAction action) {
    if (action == PlayerAction::PLAY) {
        return config.remainingPlays > 0;
    } else {
        return config.remainingDiscards > 0;
    }
}

void RunSessionService::processPlayerAction(const PlayerActionRequest& request) {
    if (request.action == PlayerAction::PLAY) {
        processPlayAction(request.selectedIndices);
    } else {
        processDiscardAction(request.selectedIndices);
    }
}

void RunSessionService::processPlayAction(const std::vector<int>& selectedIndices) {
    ChosenHand chosenHand = gameManager.createChosenHand(state.handState, selectedIndices);
    PlayedHandResult result = gameManager.resolveHand(chosenHand);
    ScoreContext context = gameManager.createScoreContext(result);
    gameManager.applyJokers(context);
    gameManager.printResult(result, context);
    state.currentScore += context.getFinalScore();
    config.remainingPlays--;
}

void RunSessionService::processDiscardAction(const std::vector<int>& selectedIndices) {
    gameManager.discardAndRedraw(state.handState, state.deck, selectedIndices, 8);
    std::cout << "\nHand after discard and redraw:\n";
    gameManager.printCards(state.handState.getCards());
    config.remainingDiscards--;
}

void RunSessionService::printSessionStatus() {
    gameManager.printGeneratedHand(state.handState);
    std::cout << "Remaining plays: " << config.remainingPlays << ", Remaining discards: " << config.remainingDiscards << "\n";
    std::cout << "Current score: " << state.currentScore << "\n";
}

void RunSessionService::printSessionResult() {
    std::cout << "Session ended. Final score: " << state.currentScore << "\n";
}