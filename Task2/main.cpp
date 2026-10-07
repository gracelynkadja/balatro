#include <memory>

#include "GameSession.h"
#include "RandomPlayerAction.h"
#include "SimpleCombatResolver.h"
#include "SimpleRewardRule.h"
#include "StatusSystem.h"

// main() hanya merakit (wiring) komponen, tanpa logika game.
int main() {
    auto playerAction   = std::make_unique<RandomPlayerAction>();
    auto combatResolver = std::make_unique<SimpleCombatResolver>();
    auto rewardRule     = std::make_unique<SimpleRewardRule>();

    GameSession session(std::move(playerAction),
                         std::move(combatResolver),
                         std::move(rewardRule),
                         StatusSystem{},
                         /*totalRooms=*/3,
                         /*startingHP=*/20);
    session.StartGame();
    return 0;
}
