#pragma once

#include "ChosenHand.h"
#include "PlayedHandResult.h"
#include "PokerHandEvaluator.h"
#include "ScoringRule.h"

class HandResolver {
public:
    HandResolver(
        const PokerHandEvaluator& evaluator,
        const ScoringRule& scoringRule
    );

    PlayedHandResult resolve(const ChosenHand& chosenHand) const;

private:
    const PokerHandEvaluator& evaluator;
    const ScoringRule& scoringRule;
};
