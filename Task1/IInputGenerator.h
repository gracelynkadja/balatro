#pragma once
#include "TurnInput.h"

// MUTABLE: menghasilkan TurnInput. Cara pembuatannya boleh diganti-ganti.
class IInputGenerator {
public:
    virtual ~IInputGenerator() = default;
    virtual TurnInput generate() = 0;
};
