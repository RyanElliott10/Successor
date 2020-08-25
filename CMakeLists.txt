cmake_minimum_required(VERSION 3.16)
project(Successor)

set(CMAKE_CXX_STANDARD 20)

add_executable(Successor src/main.cpp src/moving_average_strategy.cpp src/moving_average_strategy.hpp src/datastreamer.hpp lib/fast-cpp-csv-parser/ParseCSV/csv.h)

add_subdirectory(lib/Ludere)

find_package(Boost 1.72.0)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(lib/fast-cpp-csv-parser)

target_link_libraries(Successor LINK_PUBLIC Ludere)