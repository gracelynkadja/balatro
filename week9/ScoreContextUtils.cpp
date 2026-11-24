#include "ScoreContextUtils.h"

ScoreContext createScoreContextFromResult(const PlayedHandResult& result) {
    ScoreContext context;
    context.cards = result.cards;
    context.handType = result.handType;
    context.level = result.level;
    context.chips = result.chips;
    context.mult = result.mult;
    return context;
}
