#pragma once

// MUTABLE: menghitung jumlah HP yang didapat dari skor dasar.
class IRewardRule {
public:
    virtual ~IRewardRule() = default;
    virtual int computeReward(int baseScore) const = 0;
};