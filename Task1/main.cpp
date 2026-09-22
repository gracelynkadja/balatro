#include <memory>

#include "RunSession.h"
#include "FixedInputGenerator.h"
#include "RandomInputGenerator.h"
#include "ConsoleInputGenerator.h"
#include "SimpleScoringRule.h"
#include "DirectRewardRule.h"
#include "BonusRewardRule.h"
#include "ShopSystem.h"

// main() hanya merakit (wiring) komponen, tanpa logika game.
int main() {
    // ---- Base system (sebelum modifikasi) ----
    // auto input  = std::make_unique<FixedInputGenerator>(3);
    // auto reward = std::make_unique<DirectRewardRule>();

    // ---- Modification 1 & 2 ----
    // auto input  = std::make_unique<RandomInputGenerator>();

    // ---- Input dari luar (keyboard) ----
    auto input  = std::make_unique<ConsoleInputGenerator>(1, 6);
    auto reward = std::make_unique<BonusRewardRule>();

    auto scoring = std::make_unique<SimpleScoringRule>();

    RunSession session(std::move(input),
                       std::move(scoring),
                       std::move(reward),
                       ShopSystem{});
    session.run();
    return 0;
}
