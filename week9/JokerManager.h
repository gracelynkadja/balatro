#pragma once

#include "Joker.h"

#include <memory>
#include <vector>

class JokerManager {
public:
    void addJoker(std::unique_ptr<Joker> joker);
    void notifyScoreCalculated(ScoreContext& context) const;
    void notifyScoreCalculatedWithLog(ScoreContext& context) const;
    int size() const;

private:
    std::vector<std::unique_ptr<Joker>> jokers;
};
