cmake_minimum_required(VERSION 3.16)
project(bagel-tests)

set(INSTALL_GTEST OFF)

enable_testing()

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

add_executable(test_timer chrono/test_timer.cpp)
target_link_libraries(test_timer
    PRIVATE
        bagel::bagel
        GTest::gtest_main
)
gtest_discover_tests(test_timer)

