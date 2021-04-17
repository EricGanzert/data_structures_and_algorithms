#pragma once

#include <chrono>

class SteadyClock {
public:
    virtual std::chrono::steady_clock::time_point now();
};

