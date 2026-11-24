#pragma once
#include "HandGenerator.h"
#include "HandPlayer.h"
#include "HandResolver.h"
#include "JokerSystem.h"
#include "BlindRule.h"
#include "RewardRule.h"

// Orchestrates one Week 8-style round: 3 plays, 3 discards, and one blind.
class GameManager {
public:
    void runSession();

private:
    HandGenerator handGenerator_;
    HandPlayer handPlayer_;
    HandResolver handResolver_;
    JokerManager jokerManager_;
    BlindRule blindRule_;
    RewardRule rewardRule_;
    int money_ = 4;
};
