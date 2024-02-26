#include <bagel/chrono/timer.hpp>
#include <chrono>
#include <ctime>

namespace bagel {

void WallTimer::start() { start_ = std::chrono::steady_clock::now(); }

std::chrono::duration<double> WallTimer::stop() {
    return std::chrono::steady_clock::now() - start_;
}

void CpuTimer::start() { start_ = std::clock(); }

std::chrono::duration<double> CpuTimer::stop() {
    std::chrono::duration<double> end{(std::clock() - start_)
                                      / (double)CLOCKS_PER_SEC};
    return end;
}

}  // namespace bagel
