#pragma once

// MUTABLE: menghitung jumlah uang yang didapat (money gain) dari skor dasar.
class IRewardRule {
public:
    virtual ~IRewardRule() = default;
    virtual int computeReward(int baseScore) const = 0;
};
