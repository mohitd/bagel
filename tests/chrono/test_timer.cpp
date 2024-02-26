#include <gtest/gtest.h>

#include <chrono>
#include <thread>

#include "bagel/chrono/timer.hpp"

using namespace std::chrono_literals;

TEST(WallTimer, Basic) {
    bagel::WallTimer t;
    t.start();
    std::this_thread::sleep_for(10ms);
    auto elapsed = t.stop();
    EXPECT_LT(std::abs(elapsed.count() - 0.010), 0.005);
}

TEST(WallTimer, MultipleEnds) {
    bagel::WallTimer t;
    t.start();
    {
        std::this_thread::sleep_for(10ms);
        auto elapsed = t.stop();
        EXPECT_LT(std::abs(elapsed.count() - 0.010), 0.005);
    }
    {
        std::this_thread::sleep_for(10ms);
        auto elapsed = t.stop();
        EXPECT_LT(std::abs(elapsed.count() - 0.020), 0.005);
    }
}

TEST(CpuTimer, Basic) {
    bagel::CpuTimer t;
    t.start();
    for (int i = 0; i < 1e6; ++i) {
    }
    auto elapsed = t.stop();
    EXPECT_GT(elapsed.count(), 0);
}

TEST(CpuTimer, MultipleEnds) {
    bagel::CpuTimer t;
    t.start();
    {
        for (int i = 0; i < 1e6; ++i) {
        }
        auto elapsed = t.stop();
        EXPECT_GT(elapsed.count(), 0);
    }
    {
        for (int i = 0; i < 1e6; ++i) {
        }
        auto elapsed = t.stop();
        EXPECT_GT(elapsed.count(), 0);
    }
}
