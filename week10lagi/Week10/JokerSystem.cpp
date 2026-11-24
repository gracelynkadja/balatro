#include "JokerSystem.h"
#include <iostream>

void LuckyJoker::onScoreCalculated(ScoreContext& context) {
    context.finalScore += 25;
    std::cout << "Lucky Joker: +25 poin\n";
}

void PairJoker::onScoreCalculated(ScoreContext& context) {
    if (context.handType != HandType::HighCard) {
        context.finalScore *= 2;
        std::cout << "Pair Joker aktif: skor x2\n";
    } else {
        std::cout << "Pair Joker tidak aktif (butuh minimal Pair).\n";
    }
}

JokerManager::JokerManager() {
    jokers_.push_back(std::make_unique<LuckyJoker>());
    jokers_.push_back(std::make_unique<PairJoker>());
}

void JokerManager::notifyScoreCalculated(ScoreContext& context) const {
    for (const std::unique_ptr<Joker>& joker : jokers_) {
        if (joker) joker->onScoreCalculated(context);
    }
}
