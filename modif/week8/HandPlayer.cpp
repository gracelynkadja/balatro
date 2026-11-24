#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include "HandPlayer.h"

static std::string displayRankName(int rank) {
    switch (rank) {
        case 11: return "J";
        case 12: return "Q";
        case 13: return "K";
        case 14: return "A";
        default: return std::to_string(rank);
    }
}

ChosenHand HandPlayer::chooseHand(const Hand& hand) {
    ChosenHand chosen(hand);

    std::cout << "\n=== KARTU YANG TERSEDIA ===\n";
    for (size_t i = 0; i < hand.cards.size(); ++i) {
        std::cout << (i + 1) << ". " << displayRankName(hand.cards[i].rank)
                  << hand.cards[i].suit << "\n";
    }

    while (true) {
        std::cout << "\nPilih 1-5 kartu dengan nomor (contoh: 1 3 5): ";
        std::string line;
        if (!std::getline(std::cin, line)) {
            std::cin.clear();
            line.clear();
        }

        std::istringstream input(line);
        std::set<int> indices;
        int number;
        bool invalid = false;
        while (input >> number) {
            if (number < 1 || number > static_cast<int>(hand.cards.size()) ||
                !indices.insert(number).second) {
                invalid = true;
                break;
            }
        }
        if (!input.eof()) invalid = true;
        if (indices.empty() || indices.size() > ChosenHand::MAX_CARDS) invalid = true;

        if (invalid) {
            std::cout << "Input tidak valid. Pilih 1 sampai 5 nomor kartu yang berbeda.\n";
            continue;
        }

        chosen.clear();
        for (int index : indices) chosen.selectCard(index - 1);
        return chosen;
    }
}

void HandPlayer::playHand(const ChosenHand& chosen) {
    if (!chosen.isValid()) {
        std::cout << "Invalid hand: pilih 1-" << ChosenHand::MAX_CARDS << " kartu.\n";
        return;
    }
    std::cout << "Kartu yang dimainkan: ";
    chosen.print();
}
