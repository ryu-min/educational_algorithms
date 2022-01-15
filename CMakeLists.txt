cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME "educational_algorithms")
set(CMAKE_CXX_STANDARD 17)
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")

project("${PROJECT_NAME}")

file(GLOB_RECURSE SOURCES
        "${SOURCE_DIR}/*.h"
        "${SOURCE_DIR}/*.hpp"
        "${SOURCE_DIR}/*.cpp")

add_executable("${PROJECT_NAME}" ${SOURCES})