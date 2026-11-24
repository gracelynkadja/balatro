#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <stdexcept>
#include "GameManager.h"

static std::string cardLabel(const Card& card) {
    std::string rank;
    switch (card.rank) {
        case 11: rank = "J"; break;
        case 12: rank = "Q"; break;
        case 13: rank = "K"; break;
        case 14: rank = "A"; break;
        default: rank = std::to_string(card.rank); break;
    }
    return rank + card.suit;
}

void GameManager::runSession() {
    bool playAnotherRound = true;
    int roundNumber = 1;

    while (playAnotherRound) {
        std::cout << "\n========== RONDE " << roundNumber << " ==========\n";
        handGenerator.startNewRound();
        Hand hand = handGenerator.generateHand(8);
        int handsRemaining = 3;
        int discardsRemaining = 3;
        int roundScore = 0;

        while (handsRemaining > 0) {
            std::cout << "\n----------------------------------------\n";
            std::cout << "Kesempatan hand   : " << handsRemaining << "/3\n";
            std::cout << "Kesempatan discard: " << discardsRemaining << "/3\n";

            ChosenHand chosen = handPlayer.chooseHand(hand);
            std::cout << "\nPilih tindakan:\n";
            std::cout << "1. Hand (mainkan kartu)\n";
            if (discardsRemaining > 0)
                std::cout << "2. Discard (buang kartu pilihan)\n";
            std::cout << "Pilihan: ";

            std::string action;
            if (!std::getline(std::cin, action)) {
                std::cout << "\nInput dihentikan.\n";
                return;
            }

            if (action == "2") {
                if (discardsRemaining <= 0) {
                    std::cout << "Kesempatan discard habis. Pilih Hand.\n";
                    continue;
                }

                std::vector<int> discarded = chosen.getSelectedIndices();
                std::sort(discarded.rbegin(), discarded.rend());
                std::cout << "Kartu yang dibuang: ";
                for (int index : discarded)
                    std::cout << cardLabel(hand.cards[index]) << " ";
                std::cout << "\n";

                // Hapus hanya kartu yang dipilih. Kartu yang tidak dipilih tetap.
                for (int index : discarded)
                    hand.cards.erase(hand.cards.begin() + index);

                // Isi slot kosong dengan kartu baru dari deck ronde yang sama.
                while (hand.cards.size() < 8) {
                    try {
                        hand.cards.push_back(handGenerator.drawCard());
                    } catch (const std::runtime_error&) {
                        break;
                    }
                }
                --discardsRemaining;
                std::cout << "Kartu setelah discard:\n";
                handPlayer.showHand(hand);
                std::cout << "Discard tersisa: " << discardsRemaining << "\n";
                continue; // discard tidak mengurangi kesempatan hand
            }

            if (action != "1") {
                std::cout << "Pilihan tidak valid. Silakan pilih tindakan yang tersedia.\n";
                continue;
            }

            handPlayer.playHand(chosen);
            HandType type = handChecker.check(chosen);
            std::cout << "Hand Checker: " << handChecker.name(type) << "\n";

            int baseScore = scoringRule.scoreHand(chosen);
            std::cout << "Base score: " << baseScore << "\n";
            std::cout << "--- Aktivasi Joker ---\n";
            int finalScore = jokerSystem.apply(chosen, baseScore);
            std::cout << "Final score: " << finalScore << "\n";
            roundScore += finalScore;
            --handsRemaining;

            // Kartu yang dimainkan dikeluarkan. Sisanya dipertahankan dan
            // slot kosong diisi dari deck, sehingga tangan kembali menjadi 8.
            std::vector<int> played = chosen.getSelectedIndices();
            std::sort(played.rbegin(), played.rend());
            for (int index : played)
                hand.cards.erase(hand.cards.begin() + index);
            while (hand.cards.size() < 8) {
                try {
                    hand.cards.push_back(handGenerator.drawCard());
                } catch (const std::runtime_error&) {
                    break;
                }
            }
            std::cout << "\nTotal skor ronde sementara: " << roundScore << "\n";
        }

        bool win = blindRule.checkBlind(roundScore);
        int reward = rewardRule.earnMoney(win, roundScore);
        std::cout << "\n========== HASIL RONDE " << roundNumber << " ==========\n";
        std::cout << "Total skor: " << roundScore << "\n";
        std::cout << (win ? "Blind cleared!\n" : "Blind failed.\n");
        std::cout << "Money gained: " << reward << "\n";
        std::cout << "Kesempatan hand habis.\n";
        std::cout << "Discard akan di-reset pada ronde berikutnya.\n";

        std::cout << "\nMulai ronde berikutnya? (y/n): ";
        std::string answer;
        if (!std::getline(std::cin, answer) ||
            (answer != "y" && answer != "Y" && answer != "ya" && answer != "Ya")) {
            playAnotherRound = false;
        } else {
            ++roundNumber;
        }
    }
    std::cout << "\n=== RUN ENDED ===\n";
}
