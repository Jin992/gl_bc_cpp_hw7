cmake_minimum_required(VERSION 3.1)
project(hw7)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wpedantic -Wshadow -Wundef -Wno-missing-field-initializers")

add_executable(hw7 main.cpp Employee.hpp)
