#pragma once
#include <iostream>

class ShopSystem {
public:
    void showOffer() const {
        std::cout << "[SHOP] offered: Bonus(+2) cost 2\n";
        std::cout << "[SHOP] skipped\n";
    }
};
