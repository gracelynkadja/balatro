#include "JokerManager.h"

#include <iostream>

void JokerManager::addJoker(std::unique_ptr<Joker> joker) {
    jokers.push_back(std::move(joker));
}

void JokerManager::notifyScoreCalculated(ScoreContext& context) const {
    for (const auto& joker : jokers) {
        joker->onScoreCalculated(context);
    }
}

void JokerManager::notifyScoreCalculatedWithLog(ScoreContext& context) const {
    std::cout << "\n=== Joker Effects ===\n";

    for (const auto& joker : jokers) {
        std::cout << joker->getName() << "\n";
        std::cout << "Effect: " << joker->getDescription(context) << "\n";

        joker->onScoreCalculated(context);

        std::cout << "Current: " << context.chips << " chips, "
                  << context.mult << " mult\n\n";
    }

    std::cout << "=== Final Score ===\n";
    std::cout << context.chips << " x " << context.mult
              << " = " << context.getFinalScore() << "\n";
}

int JokerManager::size() const {
    return static_cast<int>(jokers.size());
}
