#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include <cstdlib>
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

void HandPlayer::showHand(const Hand& hand) const {
    std::cout << "\n=== KARTU DI TANGAN ===\n";
    for (size_t i = 0; i < hand.cards.size(); ++i)
        std::cout << (i + 1) << ". " << displayRankName(hand.cards[i].rank)
                  << hand.cards[i].suit << "\n";
}

std::vector<int> HandPlayer::chooseIndices(const Hand& hand, const std::string& prompt) {
    showHand(hand);
    while (true) {
        std::cout << prompt;
        std::string line;
        if (!std::getline(std::cin, line)) {
            if (std::cin.eof()) {
                std::cout << "\nInput berakhir. Program dihentikan.\n";
                std::exit(0);
            }
            std::cin.clear();
            continue;
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
        if (!input.eof() || indices.empty() || indices.size() > 5) invalid = true;
        if (invalid) {
            std::cout << "Input tidak valid. Masukkan 1-5 nomor kartu yang berbeda.\n";
            continue;
        }
        return std::vector<int>(indices.begin(), indices.end());
    }
}

ChosenHand HandPlayer::chooseHand(const Hand& hand) {
    ChosenHand chosen(hand);
    std::vector<int> indices = chooseIndices(
        hand, "Pilih 1-5 kartu untuk dimainkan (contoh: 1 3 5): ");
    for (int index : indices) chosen.selectCard(index);
    return chosen;
}

std::vector<int> HandPlayer::chooseDiscard(const Hand& hand) {
    return chooseIndices(hand, "Pilih 1-5 kartu untuk dibuang (contoh: 2 4): ");
}

void HandPlayer::playHand(const ChosenHand& chosen) {
    if (!chosen.isValid()) {
        std::cout << "Invalid hand: pilih 1-5 kartu.\n";
        return;
    }
    std::cout << "Kartu yang dimainkan: ";
    chosen.print();
}
