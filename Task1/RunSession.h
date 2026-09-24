#pragma once
#include <iostream>
#include <memory>
#include <utility>

#include "IInputGenerator.h"
#include "IScoringRule.h"
#include "IRewardRule.h"
#include "ShopSystem.h"

// INVARIANT: RunSession hanya mengendalikan game loop dan urutan fase.
// Tidak ada logika input generation, scoring, atau reward di sini.
// Semua pekerjaan didelegasikan ke IInputGenerator, IScoringRule,
// IRewardRule, dan ShopSystem.
class RunSession {
public:
    static constexpr int kTotalRounds = 3;

    RunSession(std::unique_ptr<IInputGenerator> inputGenerator,
               std::unique_ptr<IScoringRule> scoringRule,
               std::unique_ptr<IRewardRule> rewardRule,
               ShopSystem shop)
        : inputGenerator_(std::move(inputGenerator)),
          scoringRule_(std::move(scoringRule)),
          rewardRule_(std::move(rewardRule)),
          shop_(shop) {}

    void run() {
        std::cout << "=== RUN START ===\n";

        for (int round = 1; round <= kTotalRounds; ++round) {
            std::cout << "\nRound " << round << "\n";

            // 1. Generate input
            TurnInput input = inputGenerator_->generate();
            std::cout << "[PLAY] input generated: " << input.value << "\n";

            // 2. Compute base score
            int baseScore = scoringRule_->computeBaseScore(input);
            std::cout << "[SCORE] base score: " << baseScore << "\n";

            // 3. Compute reward
            int gain = rewardRule_->computeReward(baseScore);

            // 4. Update money (satu-satunya tempat uang berubah)
            money_ += gain;
            std::cout << "[REWARD] gain: " << gain
                      << " | money: " << money_ << "\n";

            // 5. Shop phase
            shop_.showOffer();

            // 6. Advance round
            if (round < kTotalRounds) {
                std::cout << "[ROUND] advance to round " << (round + 1) << "\n";
            } else {
                std::cout << "[ROUND] last round finished\n";
            }
        }

        std::cout << "\n=== RUN END ===\n";
        std::cout << "Final money: " << money_ << "\n";
    }

private:
    std::unique_ptr<IInputGenerator> inputGenerator_;
    std::unique_ptr<IScoringRule> scoringRule_;
    std::unique_ptr<IRewardRule> rewardRule_;
    ShopSystem shop_;
    int money_ = 0;
};
