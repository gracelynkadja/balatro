#pragma once
class BlindRule {
public:
    bool checkBlind(int score) { return score >= target; }
private:
    int target = 100;
};
