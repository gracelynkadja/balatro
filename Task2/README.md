# Task 2 — Develop Your Own Core Loop

**Game concept:** *Dungeon Delver* — a simple turn-based dungeon crawl. The player walks through a short dungeon of rooms. In each room they choose to **Attack** or **Defend**; the room resolves into damage dealt/taken, HP and Gold are updated, and the game checks if the player has won (cleared all rooms) or lost (HP reaches 0).

## Build & Run

```bash
g++ -std=c++17 -Wall -Wextra -o task2 main.cpp
./task2
```

## Step 1 — Core Loop

1. Player selects an action (Attack or Defend)
2. System resolves combat for that action
3. Damage dealt and damage taken are calculated, and gold reward is calculated from the damage dealt
4. HP and Gold are updated
5. Check win/lose condition (HP ≤ 0 = lose, all rooms cleared = win)
6. Repeat (advance to the next room) until win or lose

## Step 2 — Invariants

**1. Which steps must never change order?**
The six steps above, in that exact order. Input (the player's action) must always come first, combat must be resolved before any reward is calculated, HP/Gold must only update after the reward is known, and the win/lose check must happen only after the state has been updated — not before.

**2. Which components must always exist?**
A component that produces the player's action, a component that resolves that action into a result, a component that turns the result into a reward, a game state (HP, Gold, room number) to update, and a component that checks whether the game has ended. Without any one of these the loop cannot complete a round.

**3. What would break if the order changes?**
If the win/lose check ran before the state update, the game could end one room too early or too late (as happened in an earlier version of this code, where the check ran after the room counter had already advanced, letting one extra room play out). If reward was calculated before combat was resolved, there would be no result yet to calculate it from. If HP updated before damage was calculated, the update would use stale or wrong numbers.

## Step 3 — Mutable Elements

1. **How the player's action is chosen** (`IPlayerAction`) — could be random, keyboard input, or an AI strategy, without changing what a "turn" means.
2. **The combat resolution rule** (`ICombatResolver`) — damage numbers, hit chance, or adding a monster HP pool are all balance decisions, not structural ones.
3. **The reward formula** (`IRewardRule`) — gold could scale differently (e.g. flat amount, random bonus, no reward on Defend) without changing when rewards are applied.
4. **Starting HP and total rooms** — these are just parameters passed into `GameSession`, not part of the loop's logic.

These are mutable because the loop does not care *how* each of these produces its answer, only *that* it produces one at the right point in the sequence. Swapping any of them out changes gameplay feel, not game structure.

## Step 4 — C++ Core Loop Skeleton

See `main.cpp` and the header files in this folder. `GameSession` plays the role shown in the task's example `GameSession::StartGame()`, but split into the six explicit phases from Step 1 instead of three generic calls. `GameSession` only orchestrates; the action, combat, and reward logic live in separate classes (`IPlayerAction`, `ICombatResolver`, `IRewardRule`), and `StatusSystem` handles printing status and the win/lose check.

## Reflection

**1. What is the invariant structure of your game?**
The invariant is the six-step phase order in `GameSession::StartGame()`: choose action, resolve combat, calculate reward, update state, check win/lose, repeat. `GameSession` decides when each phase runs, but never performs the work of any phase itself — it only calls out to the interfaces that do.

**2. What parts are mutable?**
Everything behind an interface is mutable: `IPlayerAction` (currently `RandomPlayerAction`), `ICombatResolver` (currently `SimpleCombatResolver`), and `IRewardRule` (currently `SimpleRewardRule`). The constants passed into `GameSession` — starting HP and total rooms — are also mutable, since they're just configuration, not structure. `StatusSystem`'s printed messages and exact thresholds could change too, as long as it still answers "is the game over" at the right point in the loop.

**3. If you wanted to add a new feature, which class would change?**
It depends on the feature, and that's the point of separating things this way. A new enemy type or a change to damage balance would only touch `ICombatResolver`. A smarter player (an AI that reacts to HP) would only touch `IPlayerAction`. A different economy (gold scaling with room number) would only touch `IRewardRule`. None of these require editing `GameSession`. Only a genuinely new *phase* — something that has to happen in a fixed position in the sequence, like a mid-run shop or a status-effect phase — would require changing `GameSession`, and that would be a deliberate, careful change to the invariant itself, not a routine gameplay tweak.

**4. If you changed the loop order, what would break?**
Several things could break depending on which steps were swapped. Checking win/lose before updating HP and Gold would evaluate the game's outcome using last round's numbers, so the game could end a round late or declare a win/loss based on stale state — this is exactly the bug that showed up during testing, when the win check ran after the room counter had already moved on, letting an extra room get played by mistake. Calculating reward before resolving combat would mean there is no result yet to base the reward on. Updating state before combat is resolved, or choosing a new action before the current round's state is settled, would make the round's events happen out of sequence, so HP, Gold, and room progress would no longer correctly reflect what actually happened in that room.
