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

