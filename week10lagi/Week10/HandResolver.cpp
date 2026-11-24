#include "HandResolver.h"

HandScoreResult HandResolver::resolve(const ChosenHand& chosen) const {
    const HandType type = checker_.check(chosen);
    return scoringRule_.calculate(chosen, type);
}
