#pragma once

#include <chrono>

class SteadyClock {
public:
    std::chrono::steady_clock::time_point now();
};

