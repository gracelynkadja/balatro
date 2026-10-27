#include <iostream>
#include "GameManager.h"

void GameManager::runSession() {
    std::cout << "=== Run Started ===\n";
    Hand hand = handGenerator.generateHand();
    ChosenHand chosen = handPlayer.chooseHand(hand);
    handPlayer.playHand(chosen);
    int score = scoringRule.scoreHand(chosen);
    std::cout << "Score: " << score << "\n";
    bool win = blindRule.checkBlind(score);
    int reward = rewardRule.earnMoney(win, score);
    std::cout << (win ? "Blind cleared!\n" : "Blind failed.\n");
    std::cout << "Money gained: " << reward << "\n";
    std::cout << "=== Run Ended ===\n";
}
