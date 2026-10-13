#pragma once
#include <algorithm>
#include <map>
#include <sstream>
#include <string>
#include <vector>

enum class Suit { Spades, Hearts, Clubs, Diamonds };

struct Card {
    int rank;  // 2..10, 11=J, 12=Q, 13=K, 14=A
    Suit suit;

    // Nilai chip kartu saat di-score (aturan Balatro)
    int chipValue() const {
        if (rank == 14) return 11;
        if (rank >= 10) return 10;
        return rank;
    }

    std::string toString() const {
        static const char suits[] = {'S', 'H', 'C', 'D'};
        std::string r;
        switch (rank) {
            case 11: r = "J"; break;
            case 12: r = "Q"; break;
            case 13: r = "K"; break;
            case 14: r = "A"; break;
            default: r = std::to_string(rank);
        }
        return r + suits[static_cast<int>(suit)];
    }
};

using Hand = std::vector<Card>;

// Helper: "AS KS 10H" -> Hand (dipakai untuk demo/test)
inline Hand parseHand(const std::string& text) {
    Hand hand;
    std::istringstream in(text);
    std::string tok;
    while (in >> tok) {
        char s = tok.back();
        std::string r = tok.substr(0, tok.size() - 1);
        int rank = (r == "J") ? 11 : (r == "Q") ? 12 : (r == "K") ? 13 : (r == "A") ? 14 : std::stoi(r);
        Suit suit = (s == 'S') ? Suit::Spades : (s == 'H') ? Suit::Hearts
                  : (s == 'C') ? Suit::Clubs : Suit::Diamonds;
        hand.push_back({rank, suit});
    }
    return hand;
}

namespace HandUtils {

inline std::map<int, int> rankCounts(const Hand& h) {
    std::map<int, int> m;
    for (const auto& c : h) m[c.rank]++;
    return m;
}

// Cari rank tertinggi yang muncul >= n kali
inline bool findRank(const Hand& h, int n, int& out) {
    bool found = false;
    for (const auto& [rank, cnt] : rankCounts(h))
        if (cnt >= n) { out = rank; found = true; }  // map ascending -> terakhir = tertinggi
    return found;
}

inline Hand cardsOfRank(const Hand& h, int rank) {
    Hand r;
    for (const auto& c : h) if (c.rank == rank) r.push_back(c);
    return r;
}

inline bool isFlush(const Hand& h) {
    if (h.size() != 5) return false;
    for (const auto& c : h) if (c.suit != h[0].suit) return false;
    return true;
}

inline bool isStraight(const Hand& h) {
    if (h.size() != 5) return false;
    std::vector<int> r;
    for (const auto& c : h) r.push_back(c.rank);
    std::sort(r.begin(), r.end());
    if (std::adjacent_find(r.begin(), r.end()) != r.end()) return false;  // ada rank kembar
    if (r[4] - r[0] == 4) return true;
    return r == std::vector<int>{2, 3, 4, 5, 14};  // A-2-3-4-5 (Ace sebagai 1)
}

inline bool isFiveKind(const Hand& h) {
    return h.size() == 5 && rankCounts(h).size() == 1;
}

inline bool isFullHouse(const Hand& h) {
    if (h.size() != 5) return false;
    auto m = rankCounts(h);
    if (m.size() != 2) return false;
    for (const auto& [rank, cnt] : m) if (cnt == 3) return true;
    return false;
}

}  // namespace HandUtils
