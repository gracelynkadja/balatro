#include "HandScoreTable.h"
#include <stdexcept>

HandScoreTable::HandScoreTable() {
    table[PokerHandType::HighCard] = {1, 5, 1};
    table[PokerHandType::Pair] = {1, 10, 2};
    table[PokerHandType::TwoPair] = {1, 20, 2};
    table[PokerHandType::ThreeOfAKind] = {1, 30, 3};
    table[PokerHandType::Straight] = {1, 30, 4};
    table[PokerHandType::Flush] = {1, 35, 4};
    table[PokerHandType::FullHouse] = {1, 40, 4};
    table[PokerHandType::FourOfAKind] = {1, 60, 7};
    table[PokerHandType::StraightFlush] = {1, 100, 8};
    table[PokerHandType::RoyalFlush] = {1, 100, 8};
    table[PokerHandType::FiveOfAKind] = {1, 120, 12};
    table[PokerHandType::FlushHouse] = {1, 140, 14};
    table[PokerHandType::FlushFive] = {1, 160, 16};
}

const HandScoreData& HandScoreTable::getData(PokerHandType handType) const {
    auto it = table.find(handType);

    if (it == table.end()) {
        throw std::runtime_error("PokerHandType not found in HandScoreTable");
    }

    return it->second;
}

void HandScoreTable::upgradeHand(
    PokerHandType handType,
    int chipsIncrease,
    int multIncrease
) {
    auto& data = table[handType];

    data.level += 1;
    data.chips += chipsIncrease;
    data.mult += multIncrease;
}