#include <memory>

#include "RunSession.h"
#include "RandomInputGenerator.h"
#include "SimpleScoringRule.h"
#include "BonusRewardRule.h"
#include "ShopSystem.h"

int main() {
    auto input   = std::make_unique<RandomInputGenerator>();
    auto scoring = std::make_unique<SimpleScoringRule>();
    auto reward  = std::make_unique<BonusRewardRule>();

    RunSession session(std::move(input),
                       std::move(scoring),
                       std::move(reward),
                       ShopSystem{});
    session.run();
    return 0;
}
