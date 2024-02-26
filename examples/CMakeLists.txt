cmake_minimum_required(VERSION 3.16)
project(bagel-examples)

add_executable(timer timer.cpp)
target_link_libraries(timer PRIVATE bagel::bagel)

