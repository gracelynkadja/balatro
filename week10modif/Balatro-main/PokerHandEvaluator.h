#pragma once

#include <vector>
#include <memory>
#include "PokerHandChecker.h"
#include "Card.h"

class PokerHandEvaluator {
private:
    std::vector<std::unique_ptr<PokerHandChecker>> checkers;

public:
    PokerHandEvaluator();

    PokerHandType evaluate(const std::vector<Card>& cards) const;
};