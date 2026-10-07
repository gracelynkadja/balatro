#pragma once
#include <iostream>

// Menampilkan penawaran shop (hardcoded / sederhana).
// Shop TIDAK mengubah HP, karena HP hanya boleh berubah di fase reward.
// Penawaran di sini murni placeholder dan tidak terkait dengan rumus reward.
class ShopSystem {
public:
    void showOffer() const {
        std::cout << "[SHOP] offered: Lucky Charm\n";
        std::cout << "[SHOP] skipped\n";
    }
};