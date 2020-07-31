cmake_minimum_required(VERSION 3.17)
project(Successor)

set(CMAKE_CXX_STANDARD 20)

add_executable(Successor main.cpp)

add_subdirectory(lib/Ludere)

target_link_libraries(Successor LINK_PUBLIC Ludere)