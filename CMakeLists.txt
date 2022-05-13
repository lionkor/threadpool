# This source code is licensed under the
# Creative Commons Zero v1.0 Universal License
# (CC0 1.0 Universal / CC0 1.0)
# https://creativecommons.org/publicdomain/zero/1.0/legalcode

# Author: Lion Kortlepel / @lionkor / development@kortlepel.com

cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(threadpool)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(threadpool
    src/threadpool.h src/threadpool.cpp
)

add_executable(threadpool-test
    src/threadpool-test.cpp
)

target_link_libraries(threadpool-test threadpool)

