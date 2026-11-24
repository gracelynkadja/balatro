#pragma once

#include "ScoreContext.h"

class JokerObserver {
public:
    virtual ~JokerObserver() = default;

    virtual void onScoreCalculated(ScoreContext& context) = 0;
};
