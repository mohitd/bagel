#include <bagel/chrono/timer.hpp>
#include <iostream>

void doSomething() {
    for (int i = 0; i < 1e8; ++i) {
    }
}

int main(int argc, char** argv) {
    bagel::WallTimer timer;
    timer.start();
    doSomething();
    auto elapsed = timer.stop();
    std::cout << "Time: " << elapsed.count() << "s\n";
    return 0;
}
