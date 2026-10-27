#pragma once
#include <vector>
#include "Hand.h"

// Kartu yang dipilih pemain dari Hand untuk dimainkan (maks. 5 kartu)
class ChosenHand {
public:
    static const int MAX_CARDS = 5;

    explicit ChosenHand(const Hand& source);

    bool selectCard(int index);     // pilih kartu dari hand; false jika gagal
    bool deselectCard(int index);   // batalkan pilihan
    void clear();                   // kosongkan pilihan

    bool isSelected(int index) const;
    bool isValid() const;           // 1..5 kartu terpilih
    int size() const;
    std::vector<Card> getCards() const;
    void print() const;

private:
    const Hand& source;
    std::vector<int> selectedIndices;
};
