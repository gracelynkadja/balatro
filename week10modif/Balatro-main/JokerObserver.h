#pragma once

#include "ScoreContext.h"

// Observer interface.
// Setiap Joker wajib mengimplementasikan callback saat skor selesai dihitung.
class JokerObserver {
public:
    virtual ~JokerObserver() = default;

    virtual void onScoreCalculated(ScoreContext& context) = 0;
};
