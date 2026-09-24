#pragma once
#include <iostream>

// Menampilkan penawaran shop (hardcoded / sederhana).
// Shop TIDAK mengubah uang, karena uang hanya boleh berubah di fase reward.
class ShopSystem {
public:
    void showOffer() const {
        std::cout << "[SHOP] offered: Bonus(+2) cost 2\n";
        std::cout << "[SHOP] skipped\n";
    }
};
