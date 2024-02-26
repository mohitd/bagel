/**
 * @file timer.hpp
 */
#pragma once

#include <bagel/export.hpp>
#include <chrono>
#include <ctime>

namespace bagel {

/**
 * @brief Timer to measure wall time
 *
 * This timer measures the wall time between a consecutive `start()` and `end()`
 * calls. Calling `end()` before `start()` is undefined behavior. `end()` may be
 * called multiple times to get the time elapsed since the first `start()` call.
 */
class BAGEL_EXPORT WallTimer {
public:
    /**
     * @brief Starts the wall timer
     *
     * This will overwrite the last call to `start()`
     */
    void start();

    /**
     * @brief Ends the timer and returns the elapsed time from the last
     * `start()` call
     *
     * @return duration for the elapsed time
     */
    [[nodiscard]] std::chrono::duration<double> stop();

private:
    /// timepoint for the start of the timer
    std::chrono::steady_clock::time_point start_{};
};

/**
 * @brief Timer to measure CPU time
 *
 * This timer measures the CPU time between a consecutive `start()` and `end()`
 * calls. Calling `end()` before `start()` is undefined behavior. `end()` may be
 * called multiple times to get the time elapsed since the first `start()` call.
 */
class BAGEL_EXPORT CpuTimer {
public:
    /**
     * @brief Starts the timer
     *
     * This will overwrite the last call to `start()`
     */
    void start();

    /**
     * @brief Ends the timer and returns the elapsed time from the last
     * `start()` call
     *
     * @return duration for the elapsed time
     */
    [[nodiscard]] std::chrono::duration<double> stop();

private:
    /// timepoint for the start of the timer
    std::clock_t start_{};
};

}  // namespace bagel
