#include <iostream>
#include "GameManager.h"

void GameManager::runSession() {
    std::cout << "\n========== RONDE BARU ==========\n";
    Hand hand = handGenerator.generateHand(8);
    ChosenHand chosen = handPlayer.chooseHand(hand);

    if (!chosen.isValid()) {
        std::cout << "Pilihan kartu tidak valid. Ronde dibatalkan.\n";
        return;
    }

    handPlayer.playHand(chosen);
    HandType type = handChecker.check(chosen);
    std::cout << "Hand Checker: " << handChecker.name(type) << "\n";

    int baseScore = scoringRule.scoreHand(chosen);
    std::cout << "Base score: " << baseScore << "\n";

    std::cout << "\n--- Aktivasi Joker ---\n";
    int finalScore = jokerSystem.apply(chosen, baseScore);
    std::cout << "Final score: " << finalScore << "\n";

    bool win = blindRule.checkBlind(finalScore);
    int reward = rewardRule.earnMoney(win, finalScore);
    std::cout << (win ? "Blind cleared!\n" : "Blind failed.\n");
    std::cout << "Money gained: " << reward << "\n";
    std::cout << "===============================\n";
}
