#pragma once
#include <random>
#include "IInputGenerator.h"

class RandomInputGenerator : public IInputGenerator {
public:
    RandomInputGenerator()
        : engine_(std::random_device{}()), dist_(1, 6) {}

    TurnInput generate() override {
        return TurnInput{dist_(engine_)};
    }

private:
    std::mt19937 engine_;
    std::uniform_int_distribution<int> dist_;
};
