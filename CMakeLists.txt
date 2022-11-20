cmake_minimum_required(VERSION 3.18)

project(testc)

set(CMAKE_CXX_STANDARD 14)

add_executable(roman roman.cpp)

add_executable(pi pi.cpp)

add_executable(multi_thread multi_thread.cpp)

add_executable(primes primes.cpp)

add_executable(tasker tasker.cpp)

add_executable(sender sender.cpp)

add_executable(syntax syntax.cpp)

add_executable(montecarlo montecarlo.cpp)

add_executable(dist dist.cpp)

add_executable(opt opt.cpp)

add_executable(hw hw.cpp)