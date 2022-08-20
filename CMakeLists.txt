cmake_minimum_required(VERSION 3.22)
project(RogueLike)

set(CMAKE_CXX_STANDARD 23)

add_executable(test src/main.cpp src/level.cpp include/level.hpp src/geometry.cpp include/geometry.hpp)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
target_link_libraries(test
        ${CURSES_LIBRARIES})