#pragma once
#include "IInputGenerator.h"

// Implementasi konkret awal: selalu menghasilkan input yang sama.
class FixedInputGenerator : public IInputGenerator {
public:
    explicit FixedInputGenerator(int fixedValue = 3) : fixedValue_(fixedValue) {}

    TurnInput generate() override {
        return TurnInput{fixedValue_};
    }

private:
    int fixedValue_;
};
