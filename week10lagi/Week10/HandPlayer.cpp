#include "HandPlayer.h"
#include <cctype>
#include <iostream>
#include <set>
#include <string>

void HandPlayer::showHand(const Hand& hand) const {
    std::cout << "\nCards: ";
    for (std::size_t i = 0; i < hand.cards.size(); ++i) {
        std::cout << (i + 1) << ":[" << CardToString(hand.cards[i]) << "]";
        if (i + 1 < hand.cards.size()) std::cout << ' ';
    }
    std::cout << "\n";
}

bool HandPlayer::readAction(int discardsRemaining, char& action) const {
    while (true) {
        std::cout << "\nPilih aksi:\n1. Mainkan hand\n";
        if (discardsRemaining > 0) std::cout << "2. Buang kartu (discard)\n";
        std::cout << "q. Keluar\nMasukkan pilihan: ";
        std::string input;
        if (!std::getline(std::cin, input)) return false;
        if (input == "1") { action = '1'; return true; }
        if (input == "2" && discardsRemaining > 0) { action = '2'; return true; }
        if (input == "q" || input == "Q") { action = 'q'; return true; }
        std::cout << "Pilihan tidak valid.\n";
    }
}

bool HandPlayer::chooseIndices(const Hand& hand, const std::string& prompt,
                               std::vector<int>& indices) const {
    while (true) {
        showHand(hand);
        std::cout << prompt;
        std::string input;
        if (!std::getline(std::cin, input)) return false;

        indices.clear();
        std::set<int> seen;
        bool valid = true;
        for (unsigned char ch : input) {
            if (std::isspace(ch) || ch == ',' || ch == '-') continue;
            if (!std::isdigit(ch)) { valid = false; break; }
            const int position = ch - '0';
            if (position < 1 || position > static_cast<int>(hand.cards.size())) {
                valid = false;
                break;
            }
            const int index = position - 1;
            if (!seen.insert(index).second) { valid = false; break; }
            indices.push_back(index);
        }

        if (valid && !indices.empty() && indices.size() <= ChosenHand::MAX_CARDS)
            return true;
        std::cout << "Input tidak valid. Masukkan 1-5 posisi berbeda, contoh 415 atau 4 1 5.\n";
    }
}

bool HandPlayer::chooseHand(const Hand& hand, ChosenHand& chosen) const {
    std::vector<int> indices;
    if (!chooseIndices(hand, "Pilih 1-5 kartu untuk dimainkan: ", indices)) return false;
    chosen = ChosenHand(hand);
    for (int index : indices) {
        if (!chosen.selectCard(index)) return false;
    }
    return chosen.isValid();
}

bool HandPlayer::chooseDiscard(const Hand& hand, std::vector<int>& indices) const {
    return chooseIndices(hand, "Pilih 1-5 posisi kartu untuk dibuang: ", indices);
}
