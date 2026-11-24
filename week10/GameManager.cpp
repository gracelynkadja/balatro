#include <iostream>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include "GameManager.h"

void GameManager::runSession() {
    std::cout << "\n========== BALATRO: RONDE BARU ==========\n";
    Hand hand = handGenerator.generateHand(8);
    int handsRemaining = 3;
    int discardsRemaining = 3;
    bool blindCleared = false;
    int finalScore = 0;

    while (handsRemaining > 0 && !blindCleared) {
        std::cout << "\n----------------------------------------\n";
        std::cout << "Kesempatan hand tersisa   : " << handsRemaining << "\n";
        std::cout << "Kesempatan discard tersisa: " << discardsRemaining << "\n";
        std::cout << "\nPilih aksi:\n1. Mainkan hand\n";
        if (discardsRemaining > 0) std::cout << "2. Buang kartu (discard)\n";
        std::cout << "Masukkan pilihan: ";

        std::string action;
        if (!std::getline(std::cin, action)) {
            std::cout << "\nInput berakhir. Permainan dihentikan.\n";
            return;
        }

        if (action == "2" && discardsRemaining > 0) {
            std::vector<int> discarded = handPlayer.chooseDiscard(hand);
            std::cout << "Kartu dibuang: ";
            for (int index : discarded) {
                const Card& card = hand.cards[index];
                std::cout << card.rank << card.suit << " ";
            }
            std::cout << "\n";
            for (int index : discarded) hand.cards[index] = handGenerator.drawCard();
            --discardsRemaining;
            std::cout << "Kartu baru telah dibagikan. Discard tersisa: "
                      << discardsRemaining << "\n";
            continue;
        }

        if (action != "1") {
            std::cout << "Pilihan tidak valid. Masukkan 1";
            if (discardsRemaining > 0) std::cout << " atau 2";
            std::cout << ".\n";
            continue;
        }

        ChosenHand chosen = handPlayer.chooseHand(hand);
        handPlayer.playHand(chosen);
        HandType type = handChecker.check(chosen);
        std::cout << "Hand Checker: " << handChecker.name(type) << "\n";
        int baseScore = scoringRule.scoreHand(chosen);
        std::cout << "Base score: " << baseScore << "\n";
        std::cout << "\n--- Aktivasi Joker ---\n";
        finalScore = jokerSystem.apply(chosen, baseScore);
        std::cout << "Final score: " << finalScore << "\n";

        --handsRemaining;
        blindCleared = blindRule.checkBlind(finalScore);
        if (blindCleared) {
            std::cout << "Blind cleared!\n";
            break;
        }

        // Kartu yang dimainkan dikeluarkan, kemudian tangan diisi kembali sampai 8.
        std::vector<int> played = chosen.getSelectedIndices();
        std::sort(played.rbegin(), played.rend());
        for (int index : played) hand.cards.erase(hand.cards.begin() + index);
        while (hand.cards.size() < 8) {
            try { hand.cards.push_back(handGenerator.drawCard()); }
            catch (const std::runtime_error&) { break; }
        }
    }

    int reward = rewardRule.earnMoney(blindCleared, finalScore);
    std::cout << "\n========== HASIL RONDE ==========\n";
    std::cout << (blindCleared ? "Blind berhasil dilewati!\n" : "Kesempatan hand habis. Blind gagal.\n");
    std::cout << "Hand tersisa: " << handsRemaining << "\n";
    std::cout << "Discard tersisa: " << discardsRemaining << "\n";
    std::cout << "Money gained: " << reward << "\n";
    std::cout << "================================\n";
}
