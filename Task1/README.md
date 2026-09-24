# Task 1 — Building a Balatro-Like Run

A 3-round run loop in C++17 that separates the **invariant** (phase order) from the **mutable** parts (input, scoring, reward, shop).

## Build & Run

```bash
g++ -std=c++17 -Wall -Wextra -o task1 main.cpp
./task1
```

## Structure

| File | Role |
|---|---|
| `RunSession.h` | Invariant: controls the loop and phase order only |
| `IInputGenerator.h`, `FixedInputGenerator.h`, `RandomInputGenerator.h` | Input generation (mutable) |
| `IScoringRule.h`, `SimpleScoringRule.h` | Base score (mutable) |
| `IRewardRule.h`, `DirectRewardRule.h`, `BonusRewardRule.h` | Reward (mutable) |
| `ShopSystem.h` | Prints a shop offer (mutable) |
| `main.cpp` | Wiring only, no game logic |

## Modifications

1. **Modification 1:** `FixedInputGenerator` replaced by `RandomInputGenerator` (dice 1–6).
2. **Modification 2:** `DirectRewardRule` (reward = base score) replaced by `BonusRewardRule` (reward = base score + 2).

`RunSession` was not modified in either change; only the wiring in `main()` changed.

## Reflection

**1. What is the invariant structure in your program?**
The invariant is the fixed phase order controlled by `RunSession`: generate input, compute base score, compute reward, update money, shop phase, advance round, repeated for exactly 3 rounds. `RunSession` decides *when* each step happens, never *how* it is done. As long as this order stays untouched, the run always behaves predictably.

**2. Which parts are mutable?**
`IInputGenerator` (`FixedInputGenerator`, `RandomInputGenerator`), `IScoringRule` (`SimpleScoringRule`), `IRewardRule` (`DirectRewardRule`, `BonusRewardRule`), and the content of `ShopSystem`. Each can be swapped or edited without touching the loop, which is why they are safe to change.

**3. When you replaced the InputGenerator, why didn't RunSession change?**
`RunSession` depends only on the abstract interface `IInputGenerator` and simply calls `generate()`. It does not know which concrete class is behind it. `main()` creates a `RandomInputGenerator` and injects it into `RunSession`, so only the wiring changes, not the loop. The reward change works the same way through `IRewardRule`.

**4. What would happen if scoring logic was placed inside RunSession?**
`RunSession` would have two responsibilities: ordering phases and calculating scores. Every scoring change would require editing `RunSession`, which risks breaking the phase order by accident. Scoring rules could no longer be swapped without touching the loop, testing would be harder, and the invariant would no longer be protected because the stable part and the changing part would be mixed together.
