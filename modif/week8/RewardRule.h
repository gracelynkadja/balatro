#pragma once
class RewardRule {
public:
    int earnMoney(bool win, int score) { return win ? 3 + score / 50 : 0; }
};
