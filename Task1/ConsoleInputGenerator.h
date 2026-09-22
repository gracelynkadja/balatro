#pragma once
#include <iostream>
#include <sstream>
#include <string>

#include "IInputGenerator.h"

// Input dari luar program: nilai dibaca dari keyboard (std::cin).
// Meminta ulang sampai pemain memasukkan angka bulat dalam rentang [minValue, maxValue].
// Jika input ditutup (EOF / Ctrl+D / Ctrl+Z), nilai minimum dipakai agar program tidak hang.
class ConsoleInputGenerator : public IInputGenerator {
public:
    explicit ConsoleInputGenerator(int minValue = 1, int maxValue = 6)
        : minValue_(minValue), maxValue_(maxValue) {}

    TurnInput generate() override {
        ++turn_;
        while (true) {
            std::cout << "[INPUT] Turn " << turn_ << " - masukkan angka ("
                      << minValue_ << "-" << maxValue_ << "): ";

            std::string line;
            if (!std::getline(std::cin, line)) {
                std::cout << "\n[INPUT] input ditutup, memakai nilai " << minValue_ << "\n";
                return TurnInput{minValue_};
            }

            std::istringstream iss(line);
            int value;
            char extra;
            if ((iss >> value) && !(iss >> extra) &&
                value >= minValue_ && value <= maxValue_) {
                return TurnInput{value};
            }

            std::cout << "[INPUT] tidak valid, coba lagi.\n";
        }
    }

private:
    int minValue_;
    int maxValue_;
    int turn_ = 0;
};
