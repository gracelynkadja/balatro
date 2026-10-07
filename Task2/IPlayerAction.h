#pragma once
#include "PlayerAction.h"

// MUTABLE: cara pemain memilih aksi boleh diganti-ganti
// (acak, dari keyboard, AI, dsb).
class IPlayerAction {
public:
    virtual ~IPlayerAction() = default;
    virtual PlayerAction chooseAction() = 0;
};
