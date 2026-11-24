#pragma once

#include "JokerObserver.h"

#include <string>

class Joker : public JokerObserver {
public:
    virtual ~Joker() = default;

    virtual std::string getName() const = 0;
    virtual std::string getDescription(const ScoreContext& context) const = 0;
};
