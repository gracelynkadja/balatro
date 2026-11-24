#include "JokerManager.h"

#include <iostream>
#include <utility>

void JokerManager::registerObserver(std::unique_ptr<Joker> joker) {
    if (joker) {
        observers.push_back(std::move(joker));
    }
}

void JokerManager::addJoker(std::unique_ptr<Joker> joker) {
    registerObserver(std::move(joker));
}

void JokerManager::notifyScoreCalculated(ScoreContext& context) const {
    for (const auto& observer : observers) {
        observer->onScoreCalculated(context);
    }
}

void JokerManager::notifyScoreCalculatedWithLog(ScoreContext& context) const {
    std::cout << "\n=== Joker Effects (Observer Notification) ===\n";

    for (const auto& observer : observers) {
        std::cout << observer->getName() << "\n";
        std::cout << "Effect: " << observer->getDescription(context) << "\n";

        // Setiap Joker menerima ScoreContext yang sama.
        // Perubahan dari observer sebelumnya akan terlihat oleh observer berikutnya.
        observer->onScoreCalculated(context);

        std::cout << "Current: " << context.chips << " chips, "
                  << context.mult << " mult\n\n";
    }

    std::cout << "=== Final Score ===\n";
    std::cout << context.chips << " x " << context.mult
              << " = " << context.getFinalScore() << "\n";
}

int JokerManager::size() const {
    return static_cast<int>(observers.size());
}
