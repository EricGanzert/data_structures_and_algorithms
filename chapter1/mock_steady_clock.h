#pragma once

#include "steady_clock.h"

#include <gmock/gmock.h>

class MockSteadyClock : public SteadyClock {
public:
    MOCK_METHOD(std::chrono::steady_clock::time_point, now, ());
};