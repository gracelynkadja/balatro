#pragma once
#include <iostream>
#include "GameState.h"

// Mencetak status dan menentukan apakah game sudah berakhir (menang/kalah).
// Sederhana / boleh di-hardcode.
class StatusSystem {
public:
    void printStatus(const GameState& state) const {
        std::cout << "[STATE] HP: " << state.hp
                  << " | Gold: " << state.gold << "\n";
    }

    bool isGameOver(const GameState& state, int totalRooms) const {
        if (state.hp <= 0) {
            std::cout << "[CHECK] HP habis -> GAME OVER (kalah)\n";
            return true;
        }
        if (state.room >= totalRooms) {
            std::cout << "[CHECK] semua ruangan selesai -> GAME OVER (menang)\n";
            return true;
        }
        std::cout << "[CHECK] lanjut, game belum selesai\n";
        return false;
    }
};
