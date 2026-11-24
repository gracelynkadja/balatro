#include "HandScoreTable.h"

HandScoreData HandScoreTable::get(HandType type) const {
    switch (type) {
        case HandType::HighCard: return {5, 1};
        case HandType::Pair: return {10, 2};
        case HandType::TwoPair: return {20, 2};
        case HandType::ThreeOfAKind: return {30, 3};
        case HandType::Straight: return {30, 4};
        case HandType::Flush: return {35, 4};
        case HandType::FullHouse: return {40, 4};
        case HandType::FourOfAKind: return {60, 7};
        case HandType::StraightFlush: return {100, 8};
    }
    return {0, 1};
}
