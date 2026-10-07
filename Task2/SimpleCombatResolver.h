#pragma once
#include "ICombatResolver.h"

// Implementasi konkret:
// - Attack : menyerang penuh, tapi monster balas menyerang cukup keras.
// - Defend : tidak menyerang, tapi damage yang diterima jauh lebih kecil.
class SimpleCombatResolver : public ICombatResolver {
public:
    CombatResult resolve(const PlayerAction& action) const override {
        if (action.type == ActionType::Attack) {
            return CombatResult{/*damageDealt=*/10, /*damageTaken=*/4};
        }
        return CombatResult{/*damageDealt=*/0, /*damageTaken=*/1};
    }
};
