#pragma once
#include <iostream>
#include <random>
#include <string>
#include "HandChecker.h"

struct TurnInput { Hand hand; };

// ---------------- Hand Generator ----------------
class IHandGenerator {
public:
    virtual ~IHandGenerator() = default;
    virtual TurnInput generate(int round) = 0;
};

class RandomHandGenerator : public IHandGenerator {
public:
    explicit RandomHandGenerator(unsigned seed = std::random_device{}()) : rng_(seed) {}
    TurnInput generate(int) override {
        Hand deck;
        for (int s = 0; s < 4; ++s)
            for (int r = 2; r <= 14; ++r) deck.push_back({r, static_cast<Suit>(s)});
        std::shuffle(deck.begin(), deck.end(), rng_);
        return {Hand(deck.begin(), deck.begin() + 5)};
    }
private:
    std::mt19937 rng_;
};

// ---------------- Hand Player ----------------
// Memainkan hand: mengubah kartu menjadi HandResult lewat chain checker.
class HandPlayer {
public:
    HandResult play(const Hand& hand) const { return evaluator_.evaluate(hand); }
private:
    HandEvaluator evaluator_;
};

// ---------------- Scoring Rule ----------------
class IScoringRule {
public:
    virtual ~IScoringRule() = default;
    virtual int computeScore(const HandResult& result) const = 0;
};

// score = (base chips + chip kartu yang ter-score) x mult
class DefaultScoringRule : public IScoringRule {
public:
    int computeScore(const HandResult& r) const override {
        HandInfo info = handInfo(r.type);
        int chips = info.chips;
        for (const auto& c : r.scoringCards) chips += c.chipValue();
        return chips * info.mult;
    }
};

// ---------------- Blind Rule ----------------
class IBlindRule {
public:
    virtual ~IBlindRule() = default;
    virtual std::string name(int round) const = 0;
    virtual int targetScore(int round) const = 0;
    virtual bool isCleared(int score, int round) const { return score >= targetScore(round); }
};

// Small / Big / Boss Blind (target diset kecil karena hanya 1 hand per round)
class DefaultBlindRule : public IBlindRule {
public:
    std::string name(int round) const override {
        static const char* names[] = {"Small Blind", "Big Blind", "Boss Blind"};
        return names[(round - 1) % 3];
    }
    int targetScore(int round) const override {
        static const int targets[] = {40, 70, 100};
        return targets[(round - 1) % 3];
    }
};

// ---------------- Reward Rule ----------------
class IRewardRule {
public:
    virtual ~IRewardRule() = default;
    virtual int computeReward(int baseScore, bool blindCleared, int round) const = 0;
};

class DefaultRewardRule : public IRewardRule {
public:
    int computeReward(int baseScore, bool blindCleared, int) const override {
        return baseScore / 10 + (blindCleared ? 3 : 0);
    }
};

// ---------------- Shop ----------------
class ShopSystem {
public:
    void openShop(int money) const {
        std::cout << "[SHOP] offered: Bonus(+2) cost 2 (money: " << money << ")\n";
        std::cout << "[SHOP] skipped\n";
    }
};

// ---------------- Game Manager (invariant) ----------------
// Hanya mengatur URUTAN fase. Tidak ada logika scoring/reward/input di sini.
class GameManager {
public:
    GameManager(IHandGenerator& gen, HandPlayer& player, IScoringRule& scoring,
                IBlindRule& blind, IRewardRule& reward, ShopSystem& shop, int rounds = 3)
        : gen_(gen), player_(player), scoring_(scoring), blind_(blind),
          reward_(reward), shop_(shop), rounds_(rounds) {}

    void run() {
        std::cout << "=== RUN START ===\n";
        for (int round = 1; round <= rounds_; ++round) {
            std::cout << "\nRound " << round << " - " << blind_.name(round)
                      << " (target " << blind_.targetScore(round) << ")\n";

            // 1. Generate input
            TurnInput input = gen_.generate(round);
            std::cout << "[PLAY] input generated:";
            for (const auto& c : input.hand) std::cout << ' ' << c.toString();
            std::cout << '\n';

            // 2. Compute base score
            HandResult result = player_.play(input.hand);
            int score = scoring_.computeScore(result);
            bool cleared = blind_.isCleared(score, round);
            std::cout << "[SCORE] " << handInfo(result.type).name << " | base score: " << score
                      << (cleared ? " (blind cleared)" : " (blind failed)") << '\n';

            // 3. Compute reward
            int gain = reward_.computeReward(score, cleared, round);

            // 4. Update money
            money_ += gain;
            std::cout << "[REWARD] gain: " << gain << " | money: " << money_ << '\n';

            // 5. Shop phase
            shop_.openShop(money_);

            // 6. Advance round (dilakukan oleh ++round)
        }
        std::cout << "\n=== RUN END ===\nFinal money: " << money_ << '\n';
    }

private:
    IHandGenerator& gen_;
    HandPlayer& player_;
    IScoringRule& scoring_;
    IBlindRule& blind_;
    IRewardRule& reward_;
    ShopSystem& shop_;
    int rounds_;
    int money_ = 0;
};
