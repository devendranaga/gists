cmake_minimum_required(VERSION 2.9)

project(socketlib)

include_directories(
    ./
)

set(CMAKE_C_FLAGS "-Wall -Werror -Wshadow -Wextra -lgcov -pg -fprofile-arcs -ftest-coverage -g -DCONFIG_UNIT_TESTS -D_FORTIFY_SOURCE=2 -O3 ")

add_library(socketLib socketlib.c)

