#include "GameManager.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace {
    constexpr int InitialHandSize = 8;
    constexpr int MaxHands = 3;
    constexpr int MaxDiscards = 3;

    void RemoveSelectedCards(Hand& hand, const std::vector<int>& positions) {
        std::vector<int> descending = positions;
        std::sort(descending.rbegin(), descending.rend());
        for (int index : descending)
            hand.cards.erase(hand.cards.begin() + index);
    }

    void RefillHand(Hand& hand, HandGenerator& generator, int count) {
        int drawn = 0;
        for (int i = 0; i < count; ++i) {
            try {
                hand.cards.push_back(generator.drawCard());
                ++drawn;
            } catch (const std::runtime_error&) {
                break;
            }
        }
        std::cout << "Kartu pengganti: " << drawn
                  << " | Jumlah kartu sekarang: " << hand.cards.size() << "\n";
    }
}

void GameManager::runSession() {
    std::cout << "\n========== BALATRO-LIKE: WEEK 10 ==========\n";
    std::cout << "Starting money: $" << money_ << "\n";
    std::cout << "Blind target: " << blindRule_.target() << "\n";

    Hand hand = handGenerator_.generateHand(InitialHandSize);
    HandChecker handChecker;
    int handsRemaining = MaxHands;
    int discardsRemaining = MaxDiscards;
    bool blindCleared = false;
    int finalScore = 0;

    while (handsRemaining > 0 && !blindCleared) {
        std::cout << "\n----------------------------------------\n";
        std::cout << "Kesempatan hand tersisa   : " << handsRemaining << "\n";
        std::cout << "Kesempatan discard tersisa: " << discardsRemaining << "\n";

        char action = '\0';
        if (!handPlayer_.readAction(discardsRemaining, action)) {
            std::cout << "\nInput berakhir. Permainan dihentikan.\n";
            return;
        }
        if (action == 'q') {
            std::cout << "Permainan dihentikan pemain. Money: $" << money_ << "\n";
            return;
        }

        if (action == '2') {
            std::vector<int> discardedIndices;
            if (!handPlayer_.chooseDiscard(hand, discardedIndices)) {
                std::cout << "\nInput berakhir. Permainan dihentikan.\n";
                return;
            }

            std::cout << "Kartu dibuang: ";
            for (int index : discardedIndices)
                std::cout << '[' << CardToString(hand.cards.at(static_cast<std::size_t>(index))) << "] ";
            std::cout << "\n";

            // Week 8 keeps the other card positions stable: each discarded slot is replaced in-place.
            int replacements = 0;
            for (int index : discardedIndices) {
                try {
                    hand.cards.at(static_cast<std::size_t>(index)) = handGenerator_.drawCard();
                    ++replacements;
                } catch (const std::runtime_error&) {
                    break;
                }
            }
            std::cout << "Kartu pengganti: " << replacements
                      << " | Jumlah kartu sekarang: " << hand.cards.size() << "\n";
            --discardsRemaining;
            std::cout << "Discard tersisa: " << discardsRemaining << "\n";
            continue;
        }

        ChosenHand chosen;
        if (!handPlayer_.chooseHand(hand, chosen)) {
            std::cout << "\nInput berakhir. Permainan dihentikan.\n";
            return;
        }

        std::cout << "Chosen Hand: ";
        chosen.print();

        // HandResolver runs HandChecker first, then calculates the base score.
        const HandScoreResult result = handResolver_.resolve(chosen);
        ScoreContext context;
        context.handType = result.handType;
        context.chips = result.chips;
        context.mult = result.mult;
        context.baseScore = result.baseScore;
        context.finalScore = result.baseScore;

        // Notify Joker observers only after HandRank and base score are known.
        std::cout << "--- Aktivasi Joker ---\n";
        jokerManager_.notifyScoreCalculated(context);
        finalScore = context.finalScore;

        std::cout << "Hand Checker: " << handChecker.name(result.handType) << "\n";
        std::cout << "Base Chips: " << result.chips
                  << " | Base Mult: " << result.mult
                  << " | Base score: " << result.baseScore << "\n";
        std::cout << "Final hand score: " << finalScore << "\n";

        --handsRemaining;
        blindCleared = blindRule_.checkBlind(finalScore);
        std::cout << "Blind target: " << blindRule_.target()
                  << " | Hands left: " << handsRemaining << "\n";

        if (blindCleared) {
            std::cout << "BLIND CLEARED!\n";
            break;
        }

        // Remove played cards and refill by exactly the number played.
        const std::vector<int> playedIndices = chosen.getSelectedIndices();
        RemoveSelectedCards(hand, playedIndices);
        RefillHand(hand, handGenerator_, chosen.size());
    }

    const int reward = rewardRule_.earnMoney(blindCleared, finalScore);
    money_ += reward;

    std::cout << "\n========== HASIL RONDE ==========\n";
    std::cout << (blindCleared ? "Blind berhasil dilewati!\n"
                               : "Kesempatan hand habis. Blind gagal.\n");
    std::cout << "Hand tersisa: " << handsRemaining << "\n";
    std::cout << "Discard tersisa: " << discardsRemaining << "\n";
    std::cout << "Money gained: $" << reward << "\n";
    std::cout << "Total money: $" << money_ << "\n";
    std::cout << "================================\n";
}
