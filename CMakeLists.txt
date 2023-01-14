cmake_minimum_required(VERSION 3.23)
project(test)

set(CMAKE_CXX_STANDARD 14)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
add_executable(test main.cpp display.hpp engine.cpp display.cpp menu.cpp menu.hpp engine.hpp main.hpp)
target_link_libraries(test ${CURSES_LIBRARIES})