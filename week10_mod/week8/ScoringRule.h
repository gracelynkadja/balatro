#pragma once
#include "ChosenHand.h"
#include "HandChecker.h"
class ScoringRule {
public:
    int scoreHand(const ChosenHand& chosen);
private:
    HandChecker checker;
};
