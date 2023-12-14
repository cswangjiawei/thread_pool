cmake_minimum_required(VERSION 3.5)#最低CMake版本
project(thread_pool)

set(SOURCES src/example.cpp src/thread_pool.cpp)
add_executable(example ${SOURCES})

message("PROJECT_SOURCE _DIR = ${PROJECT_SOURCE_DIR}")

target_include_directories(example PRIVATE ${PROJECT_SOURCE_DIR}/include)
