cmake_minimum_required(VERSION 4.0)
project(Euro_coin_collector)

set(CMAKE_CXX_STANDARD 20)

add_executable(Euro_coin_collector main.cpp
        country.cpp
        country.h)
