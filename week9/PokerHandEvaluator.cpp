#include "PokerHandEvaluator.h"

// include semua checker
#include "FlushFiveChecker.h"
#include "FlushHouseChecker.h"
#include "FiveOfAKindChecker.h"
#include "RoyalFlushChecker.h"
#include "StraightFlushChecker.h"
#include "FourOfAKindChecker.h"
#include "FullHouseChecker.h"
#include "FlushChecker.h"
#include "StraightChecker.h"
#include "ThreeOfAKindChecker.h"
#include "TwoPairChecker.h"
#include "PairChecker.h"
#include "HighCardChecker.h"

PokerHandEvaluator::PokerHandEvaluator() {
    checkers.push_back(std::make_unique<FlushFiveChecker>());
    checkers.push_back(std::make_unique<FlushHouseChecker>());
    checkers.push_back(std::make_unique<FiveOfAKindChecker>());
    checkers.push_back(std::make_unique<RoyalFlushChecker>());
    checkers.push_back(std::make_unique<StraightFlushChecker>());
    checkers.push_back(std::make_unique<FourOfAKindChecker>());
    checkers.push_back(std::make_unique<FullHouseChecker>());
    checkers.push_back(std::make_unique<FlushChecker>());
    checkers.push_back(std::make_unique<StraightChecker>());
    checkers.push_back(std::make_unique<ThreeOfAKindChecker>());
    checkers.push_back(std::make_unique<TwoPairChecker>());
    checkers.push_back(std::make_unique<PairChecker>());
    checkers.push_back(std::make_unique<HighCardChecker>());
}

PokerHandType PokerHandEvaluator::evaluate(const std::vector<Card>& cards) const {
    for (const auto& checker : checkers) {
        if (checker->checkPokerHand(cards)) {
            return checker->getHandType();
        }
    }
    return PokerHandType::None;
}