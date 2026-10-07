#pragma once
#include <iostream>
#include <memory>
#include <utility>

#include "IPlayerAction.h"
#include "ICombatResolver.h"
#include "IRewardRule.h"
#include "StatusSystem.h"
#include "GameState.h"

// INVARIANT: GameSession hanya mengendalikan game loop dan urutan fase.
// Tidak ada logika pemilihan aksi, resolve combat, atau reward di sini.
// Semua pekerjaan didelegasikan ke IPlayerAction, ICombatResolver,
// IRewardRule, dan StatusSystem.
class GameSession {
public:
    GameSession(std::unique_ptr<IPlayerAction> playerAction,
                std::unique_ptr<ICombatResolver> combatResolver,
                std::unique_ptr<IRewardRule> rewardRule,
                StatusSystem statusSystem,
                int totalRooms = 3,
                int startingHP = 20)
        : playerAction_(std::move(playerAction)),
          combatResolver_(std::move(combatResolver)),
          rewardRule_(std::move(rewardRule)),
          statusSystem_(statusSystem),
          totalRooms_(totalRooms),
          state_{startingHP, 0, 1} {}

    void StartGame() {
        std::cout << "=== GAME START ===\n";

        bool gameOver = false;
        while (!gameOver) {
            std::cout << "\nRoom " << state_.room << "\n";

            // 1. Player selects action
            PlayerAction action = playerAction_->chooseAction();
            std::cout << "[ACTION] player chose: "
                      << (action.type == ActionType::Attack ? "Attack" : "Defend")
                      << "\n";

            // 2. System resolves combat
            CombatResult result = combatResolver_->resolve(action);
            std::cout << "[COMBAT] damage dealt: " << result.damageDealt
                      << " | damage taken: " << result.damageTaken << "\n";

            // 3. Damage / reward calculated
            int goldGain = rewardRule_->computeGold(result);
            std::cout << "[REWARD] gold gained: " << goldGain << "\n";

            // 4. Game state updates (HP & Gold)
            state_.hp -= result.damageTaken;
            state_.gold += goldGain;
            statusSystem_.printStatus(state_);

            // 5. Check win/lose condition
            gameOver = statusSystem_.isGameOver(state_, totalRooms_);

            // 6. Repeat (advance to next room)
            if (!gameOver) {
                state_.room++;
                std::cout << "[ROOM] advance to room " << state_.room << "\n";
            }
        }

        std::cout << "\n=== GAME END ===\n";
        std::cout << "Final HP: " << state_.hp << " | Final Gold: " << state_.gold << "\n";
    }

private:
    std::unique_ptr<IPlayerAction> playerAction_;
    std::unique_ptr<ICombatResolver> combatResolver_;
    std::unique_ptr<IRewardRule> rewardRule_;
    StatusSystem statusSystem_;
    int totalRooms_;
    GameState state_;
};
