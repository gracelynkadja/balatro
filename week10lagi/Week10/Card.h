#pragma once
#include <string>

// Rank: 2-14 (11=J, 12=Q, 13=K, 14=A). Suit: H, D, C, S.
struct Card {
    int rank = 2;
    char suit = 'S';
};

inline std::string RankName(int rank) {
    switch (rank) {
        case 11: return "J";
        case 12: return "Q";
        case 13: return "K";
        case 14: return "A";
        default: return std::to_string(rank);
    }
}

inline std::string SuitSymbol(char suit) {
    switch (suit) {
        case 'H': return "♥";
        case 'D': return "♦";
        case 'C': return "♣";
        case 'S': return "♠";
        default: return "?";
    }
}

inline std::string CardToString(const Card& card) {
    return RankName(card.rank) + SuitSymbol(card.suit);
}

inline int CardChipValue(const Card& card) {
    if (card.rank >= 11 && card.rank <= 13) return 10;
    if (card.rank == 14) return 11;
    return card.rank;
}
