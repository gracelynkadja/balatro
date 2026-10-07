#pragma once
#include "PlayerAction.h"
#include "CombatResult.h"

// MUTABLE: aturan bagaimana sebuah aksi diselesaikan menjadi hasil combat.
class ICombatResolver {
public:
    virtual ~ICombatResolver() = default;
    virtual CombatResult resolve(const PlayerAction& action) const = 0;
};
