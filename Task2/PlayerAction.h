#pragma once

// Jenis aksi yang bisa dipilih pemain tiap ruangan.
enum class ActionType {
    Attack,
    Defend
};

struct PlayerAction {
    ActionType type;
};
