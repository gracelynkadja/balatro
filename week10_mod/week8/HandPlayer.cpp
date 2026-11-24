#include <iostream>
#include <cstdlib>
#include <sstream>
#include <set>
#include <string>
#include "HandPlayer.h"

static std::string rankLabel(int rank) {
    switch (rank) {
        case 11: return "J";
        case 12: return "Q";
        case 13: return "K";
        case 14: return "A";
        default: return std::to_string(rank);
    }
}

void HandPlayer::showHand(const Hand& hand) const {
    std::cout << "\n=== 8 KARTU YANG TERSEDIA ===\n";
    for (size_t i = 0; i < hand.cards.size(); ++i) {
        std::cout << (i + 1) << ". " << rankLabel(hand.cards[i].rank)
                  << hand.cards[i].suit << "\n";
    }
}

ChosenHand HandPlayer::chooseHand(const Hand& hand) {
    ChosenHand chosen(hand);
    while (true) {
        showHand(hand);
        std::cout << "Pilih 1-5 kartu (contoh: 1 3 5): ";
        std::string line;
        if (!std::getline(std::cin, line)) {
            std::cout << "\nInput dihentikan.\n";
            std::exit(0);
        }
        std::istringstream input(line);
        std::set<int> indices;
        int number;
        bool invalid = false;
        while (input >> number) {
            if (number < 1 || number > static_cast<int>(hand.cards.size()) ||
                !indices.insert(number - 1).second) {
                invalid = true;
                break;
            }
        }
        if (!input.eof() || indices.empty() || indices.size() > ChosenHand::MAX_CARDS)
            invalid = true;
        if (invalid) {
            std::cout << "Input tidak valid. Pilih 1-5 nomor kartu yang berbeda.\n";
            continue;
        }
        for (int index : indices) chosen.selectCard(index);
        return chosen;
    }
}

void HandPlayer::playHand(const ChosenHand& chosen) {
    std::cout << "Kartu yang dimainkan: ";
    chosen.print();
}
