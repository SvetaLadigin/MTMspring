cmake_minimum_required(VERSION 3.10)
project(mtm_ex3)

set(CMAKE_CXX_STANDARD 11)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic-errors -Werror")

add_executable(test1 test1.cpp eurovision.h eurovision.cpp)
add_executable(face_tests_part1 face_tests_part1/finaltest.cpp
        face_tests_part1/test1.cpp
        face_tests_part1/test2.cpp
        face_tests_part1/test3.cpp
        face_tests_part1/test4.cpp
        face_tests_part1/test5.cpp
        face_tests_part1/test6.cpp
        face_tests_part1/test7.cpp
        face_tests_part1/test8.cpp
        face_tests_part1/test9.cpp
        face_tests_part1/test10.cpp
        eurovision.h eurovision.cpp)
target_include_directories(face_tests_part1 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} face_tests_part1)