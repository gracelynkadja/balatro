#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Card.h"

// Urutan dari terlemah ke terkuat (sesuai Balatro; Royal Flush = Straight Flush A-high)
enum class HandType {
    HighCard, Pair, TwoPair, ThreeOfAKind, Straight, Flush, FullHouse,
    FourOfAKind, StraightFlush, RoyalFlush, FiveOfAKind, FlushHouse, FlushFive
};

struct HandInfo { std::string name; int chips; int mult; };

inline HandInfo handInfo(HandType t) {
    switch (t) {
        case HandType::HighCard:      return {"High Card", 5, 1};
        case HandType::Pair:          return {"Pair", 10, 2};
        case HandType::TwoPair:       return {"Two Pair", 20, 2};
        case HandType::ThreeOfAKind:  return {"Three of a Kind", 30, 3};
        case HandType::Straight:      return {"Straight", 30, 4};
        case HandType::Flush:         return {"Flush", 35, 4};
        case HandType::FullHouse:     return {"Full House", 40, 4};
        case HandType::FourOfAKind:   return {"Four of a Kind", 60, 7};
        case HandType::StraightFlush: return {"Straight Flush", 100, 8};
        case HandType::RoyalFlush:    return {"Royal Flush", 100, 8};
        case HandType::FiveOfAKind:   return {"Five of a Kind", 120, 12};
        case HandType::FlushHouse:    return {"Flush House", 140, 14};
        case HandType::FlushFive:     return {"Flush Five", 160, 16};
    }
    return {"Unknown", 0, 0};
}

struct HandResult {
    HandType type;
    Hand scoringCards;  // hanya kartu yang ikut menyumbang chip
};

// ---------------- Handler (Chain of Responsibility) ----------------
class HandChecker {
public:
    virtual ~HandChecker() = default;

    HandChecker* setNext(HandChecker* n) { next_ = n; return n; }

    HandResult check(const Hand& hand) const {
        Hand scoring;
        if (matches(hand, scoring)) return {type(), scoring};
        if (next_) return next_->check(hand);
        return {HandType::HighCard, {}};  // ujung chain (hand kosong)
    }

protected:
    virtual HandType type() const = 0;
    virtual bool matches(const Hand& hand, Hand& scoring) const = 0;

private:
    HandChecker* next_ = nullptr;
};

// ---------------- Concrete Checkers ----------------
class FlushFiveChecker : public HandChecker {
    HandType type() const override { return HandType::FlushFive; }
    bool matches(const Hand& h, Hand& s) const override {
        if (!HandUtils::isFiveKind(h) || !HandUtils::isFlush(h)) return false;
        s = h; return true;
    }
};

class FlushHouseChecker : public HandChecker {
    HandType type() const override { return HandType::FlushHouse; }
    bool matches(const Hand& h, Hand& s) const override {
        if (!HandUtils::isFullHouse(h) || !HandUtils::isFlush(h)) return false;
        s = h; return true;
    }
};

class FiveOfAKindChecker : public HandChecker {
    HandType type() const override { return HandType::FiveOfAKind; }
    bool matches(const Hand& h, Hand& s) const override {
        if (!HandUtils::isFiveKind(h)) return false;
        s = h; return true;
    }
};

class RoyalFlushChecker : public HandChecker {
    HandType type() const override { return HandType::RoyalFlush; }
    bool matches(const Hand& h, Hand& s) const override {
        if (!HandUtils::isFlush(h) || !HandUtils::isStraight(h)) return false;
        auto m = HandUtils::rankCounts(h);
        if (m.begin()->first != 10 || m.rbegin()->first != 14) return false;  // 10-J-Q-K-A
        s = h; return true;
    }
};

class StraightFlushChecker : public HandChecker {
    HandType type() const override { return HandType::StraightFlush; }
    bool matches(const Hand& h, Hand& s) const override {
        if (!HandUtils::isFlush(h) || !HandUtils::isStraight(h)) return false;
        s = h; return true;
    }
};

class FourOfAKindChecker : public HandChecker {
    HandType type() const override { return HandType::FourOfAKind; }
    bool matches(const Hand& h, Hand& s) const override {
        int r;
        if (!HandUtils::findRank(h, 4, r)) return false;
        s = HandUtils::cardsOfRank(h, r); return true;
    }
};

class FullHouseChecker : public HandChecker {
    HandType type() const override { return HandType::FullHouse; }
    bool matches(const Hand& h, Hand& s) const override {
        if (!HandUtils::isFullHouse(h)) return false;
        s = h; return true;
    }
};

class FlushChecker : public HandChecker {
    HandType type() const override { return HandType::Flush; }
    bool matches(const Hand& h, Hand& s) const override {
        if (!HandUtils::isFlush(h)) return false;
        s = h; return true;
    }
};

class StraightChecker : public HandChecker {
    HandType type() const override { return HandType::Straight; }
    bool matches(const Hand& h, Hand& s) const override {
        if (!HandUtils::isStraight(h)) return false;
        s = h; return true;
    }
};

class ThreeOfAKindChecker : public HandChecker {
    HandType type() const override { return HandType::ThreeOfAKind; }
    bool matches(const Hand& h, Hand& s) const override {
        int r;
        if (!HandUtils::findRank(h, 3, r)) return false;
        s = HandUtils::cardsOfRank(h, r); return true;
    }
};

class TwoPairChecker : public HandChecker {
    HandType type() const override { return HandType::TwoPair; }
    bool matches(const Hand& h, Hand& s) const override {
        Hand scoring;
        int pairs = 0;
        for (const auto& [rank, cnt] : HandUtils::rankCounts(h)) {
            if (cnt >= 2) {
                ++pairs;
                for (const auto& c : HandUtils::cardsOfRank(h, rank)) scoring.push_back(c);
            }
        }
        if (pairs < 2) return false;
        s = scoring; return true;
    }
};

class PairChecker : public HandChecker {
    HandType type() const override { return HandType::Pair; }
    bool matches(const Hand& h, Hand& s) const override {
        int r;
        if (!HandUtils::findRank(h, 2, r)) return false;
        s = HandUtils::cardsOfRank(h, r); return true;
    }
};

class HighCardChecker : public HandChecker {
    HandType type() const override { return HandType::HighCard; }
    bool matches(const Hand& h, Hand& s) const override {
        if (h.empty()) return false;
        s = {*std::max_element(h.begin(), h.end(),
                [](const Card& a, const Card& b) { return a.rank < b.rank; })};
        return true;
    }
};

// ---------------- Chain builder ----------------
// Urutan chain = prioritas: dari hand terkuat ke terlemah.
class HandEvaluator {
public:
    HandEvaluator() {
        add<FlushFiveChecker>();
        add<FlushHouseChecker>();
        add<FiveOfAKindChecker>();
        add<RoyalFlushChecker>();
        add<StraightFlushChecker>();
        add<FourOfAKindChecker>();
        add<FullHouseChecker>();
        add<FlushChecker>();
        add<StraightChecker>();
        add<ThreeOfAKindChecker>();
        add<TwoPairChecker>();
        add<PairChecker>();
        add<HighCardChecker>();
    }

    HandResult evaluate(const Hand& hand) const { return chain_.front()->check(hand); }

private:
    template <class T>
    void add() {
        chain_.push_back(std::make_unique<T>());
        if (chain_.size() > 1) chain_[chain_.size() - 2]->setNext(chain_.back().get());
    }
    std::vector<std::unique_ptr<HandChecker>> chain_;
};
