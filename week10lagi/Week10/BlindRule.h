#pragma once

class BlindRule {
public:
    bool checkBlind(int score) const { return score >= target_; }
    int target() const { return target_; }

private:
    int target_ = 100;
};
