#pragma once
#include <random>
#include "IPlayerAction.h"

// Implementasi konkret: memilih Attack atau Defend secara acak.
class RandomPlayerAction : public IPlayerAction {
public:
    RandomPlayerAction()
        : engine_(std::random_device{}()), dist_(0, 1) {}

    PlayerAction chooseAction() override {
        ActionType type = (dist_(engine_) == 0) ? ActionType::Attack
                                                  : ActionType::Defend;
        return PlayerAction{type};
    }

private:
    std::mt19937 engine_;
    std::uniform_int_distribution<int> dist_;
};
