#pragma once

enum class PlayerAction {
    PLAY,
    DISCARD
};

struct PlayerActionRequest {
    PlayerAction action;
    std::vector<int> selectedIndices;
};