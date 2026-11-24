#pragma once
#include <memory>
#include <string>
#include <vector>
#include "ScoringRule.h"

// Mutable context passed to Joker observers after the base score is calculated.
struct ScoreContext {
    HandType handType = HandType::HighCard;
    int chips = 0;
    int mult = 1;
    int baseScore = 0;
    int finalScore = 0;
};

class JokerObserver {
public:
    virtual ~JokerObserver() = default;
    virtual void onScoreCalculated(ScoreContext& context) = 0;
};

// A Joker is both a game entity and an observer of the score-calculated event.
class Joker : public JokerObserver {
public:
    virtual ~Joker() = default;
    virtual std::string name() const = 0;
};

class LuckyJoker final : public Joker {
public:
    void onScoreCalculated(ScoreContext& context) override;
    std::string name() const override { return "Lucky Joker"; }
};

class PairJoker final : public Joker {
public:
    void onScoreCalculated(ScoreContext& context) override;
    std::string name() const override { return "Pair Joker"; }
};

// Owns Joker entities and notifies each one after base score calculation.
class JokerManager {
public:
    JokerManager();
    void notifyScoreCalculated(ScoreContext& context) const;

private:
    std::vector<std::unique_ptr<Joker>> jokers_;
};
