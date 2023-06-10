cmake_minimum_required(VERSION 3.10)
project(COMP_EVOL)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB SOURCES "src/*.cpp" "include/*.h")
add_library(comp ${SOURCES})