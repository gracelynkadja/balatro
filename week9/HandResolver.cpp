#include "HandResolver.h"

HandResolver::HandResolver(
    const PokerHandEvaluator& evaluator,
    const ScoringRule& scoringRule
)
    : evaluator(evaluator)
    , scoringRule(scoringRule)
{
}

PlayedHandResult HandResolver::resolve(const ChosenHand& chosenHand) const {
    const std::vector<Card>& cards = chosenHand.getSelectedCards();
    const PokerHandType handType = evaluator.evaluate(cards);

    PlayedHandResult result;
    result.cards = cards;
    result.handType = handType;

    if (handType == PokerHandType::None) {
        return result;
    }

    result.level = scoringRule.getLevel(handType);
    result.chips = scoringRule.getChips(handType);
    result.mult = scoringRule.getMult(handType);
    result.finalScore = scoringRule.calculateScore(handType);

    return result;
}
